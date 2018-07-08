/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFDracoExtension.h"
#include "GLTFPrimitive.h"
#include "GLTFBuffer.h"
#include "GLTFBufferView.h"
#include "GLTFAccessor.h"

#include "draco/mesh/mesh.h"
#include "draco/compression/encode.h"
#include "draco/compression/decode.h"
#include "draco/core/cycle_timer.h"

#include <iostream>

using namespace flow;
using std::string;
using std::cout;
using std::endl;

////////////////////////////////////////////////////////////////////////////////

draco::GeometryAttribute::Type _dracoAttributeType(GLTFAttributeType type)
{
	switch (type) {
	case GLTFAttributeType::POSITION:
		return draco::GeometryAttribute::POSITION;
	case GLTFAttributeType::NORMAL:
		return draco::GeometryAttribute::NORMAL;
	case GLTFAttributeType::TEXCOORD_0:
		return draco::GeometryAttribute::TEX_COORD;
	case GLTFAttributeType::COLOR_0:
		return draco::GeometryAttribute::COLOR;
	default:
		F_ASSERT(false);  return draco::GeometryAttribute::GENERIC;
	}
}

draco::DataType _dracoComponentType(GLTFAccessorComponent component)
{
	switch (component) {
	case GLTFAccessorComponent::BYTE:
		return draco::DT_INT8;
	case GLTFAccessorComponent::UNSIGNED_BYTE:
		return draco::DT_UINT8;
	case GLTFAccessorComponent::SHORT:
		return draco::DT_INT16;
	case GLTFAccessorComponent::UNSIGNED_SHORT:
		return draco::DT_UINT16;
	case GLTFAccessorComponent::INT:
		return draco::DT_INT32;
	case GLTFAccessorComponent::UNSIGNED_INT:
		return draco::DT_UINT32;
	case GLTFAccessorComponent::FLOAT:
		return draco::DT_FLOAT32;
	default:
		F_ASSERT(false); return draco::DT_INT8;
	}
}

////////////////////////////////////////////////////////////////////////////////

GLTFDracoOptions::GLTFDracoOptions() :
	positionQuantizationBits(14),
	texCoordsQuantizationBits(12),
	normalsQuantizationBits(10),
	genericQuantizationBits(8),
	stripNormals(false),
	stripTexCoords(false),
	stripGeneric(false),
	compressionLevel(7)
{
}

////////////////////////////////////////////////////////////////////////////////

GLTFDracoExtension::GLTFDracoExtension() :
	_pBufferView(nullptr),
	_pMesh(nullptr)
{
}

GLTFDracoExtension::~GLTFDracoExtension()
{
	F_SAFE_DELETE_PTR_RANGE(buffers);
	F_SAFE_DELETE(_pMesh);
}

bool GLTFDracoExtension::encode(GLTFPrimitive* pPrimitive, GLTFBuffer* pCompressedBuffer)
{
	_pPrimitive = pPrimitive;
	_pPrimitive->addExtension(this);

	return _encodeMeshToBuffer(pCompressedBuffer);
}

void GLTFDracoExtension::setOptions(const GLTFDracoOptions& options)
{
	_dracoOptions = options;
}

const char* GLTFDracoExtension::name() const
{
	return "KHR_draco_mesh_compression";
}

json GLTFDracoExtension::toJSON() const
{
	json result{
		{ "bufferView", _pBufferView->index() }
	};

	if (!_attributes.empty()) {
		json attribDict;
		for (auto it = _attributes.begin(); it != _attributes.end(); ++it) {
			attribDict[it->type.name()] = it->index;
		}
		result["attributes"] = attribDict;
	}

	return result;
}

bool GLTFDracoExtension::_encodeMeshToBuffer(GLTFBuffer* pCompressedBuffer)
{
	// create temporary data structures for encoding
	F_SAFE_DELETE(_pMesh);
	F_SAFE_DELETE_PTR_RANGE(buffers);
	buffers.clear();

	_pMesh = new draco::Mesh();

	auto& attributes = _pPrimitive->attributes();
	for (size_t i = 0; i < attributes.size(); ++i) {
		int index = _addAttribute(attributes[i].pAccessor, attributes[i].type);
		_attributes.push_back({ attributes[i].type, index });
	}

	_addFaces(_pPrimitive->indices());

	cout << "GLTFDracoExtension::_encodeMeshToBuffer - deduplication" << endl;

	//_pMesh->DeduplicatePointIds();
	//_pMesh->DeduplicateAttributeValues();

	cout << "GLTFDracoExtension::_encodeMeshToBuffer - encode mesh" << endl;

	draco::Encoder encoder;
	draco::CycleTimer timer;
	draco::EncoderBuffer buffer;

	timer.Start();
	const draco::Status status = encoder.EncodeMeshToBuffer(*_pMesh, &buffer);
	timer.Stop();

	cout << "GLTFDracoExtension::_encodeMeshToBuffer - done encoding" << endl;

	// dispose of temporary data structures
	F_SAFE_DELETE(_pMesh);
	F_SAFE_DELETE_PTR_RANGE(buffers);
	buffers.clear();

	if (!status.ok()) {
		cout << "Failed to encode the mesh." << endl;
		cout << status.error_msg() << endl;
		return false;
	}
	else {
		cout << "Successfully encoded the mesh." << endl;
	}

	cout << "GLTFDracoExtension::_encodeMeshToBuffer - write buffer" << endl;

	_pBufferView = pCompressedBuffer->addData(buffer.data(), buffer.size());
	return true;
}

void GLTFDracoExtension::_addFaces(const GLTFAccessor* pIndicesAccessor)
{
	GLTFAccessorComponent component = pIndicesAccessor->component();
	int numAttribs = _pMesh->num_attributes();

	size_t pointCount = pIndicesAccessor->elementCount();
	size_t faceCount = pointCount / 3;

	cout << endl << "FACES/MAPPING" << endl;
	cout << "num attribs: " << numAttribs << endl;
	cout << "point count: " << pointCount << endl;
	cout << "face count: " << faceCount << endl;

	_pMesh->set_num_points(uint32_t(pointCount));
	_pMesh->SetNumFaces(uint32_t(faceCount));

	// add faces
	for (size_t i = 0; i < faceCount; ++i) {
		draco::Mesh::Face face;
		for (size_t c = 0; c < 3; ++c) {
			face[c] = uint32_t(3 * i + c);
		}
		_pMesh->SetFace(draco::FaceIndex(uint32_t(i)), face);
	}

	for (int j = 0; j < numAttribs; ++j) {
		_pMesh->attribute(j)->SetExplicitMapping(pointCount);
	}

	// add attribute mappings
	switch (component) {
	case GLTFAccessorComponent::UNSIGNED_INT:
	{
		const uint32_t* pData = (const uint32_t*)pIndicesAccessor->data();
		uint32_t maxIndex = 0;

		for (size_t i = 0; i < pointCount; ++i) {
			maxIndex = max(maxIndex, pData[i]);
			for (int j = 0; j < numAttribs; ++j) {
				_pMesh->attribute(j)->SetPointMapEntry(draco::PointIndex(uint32_t(i)), draco::AttributeValueIndex(pData[i]));
			}
		}

		cout << "max index: " << maxIndex << endl;
	}
	break;

	case GLTFAccessorComponent::UNSIGNED_SHORT:
	{
		const uint16_t* pData = (const uint16_t*)pIndicesAccessor->data();

		for (size_t i = 0; i < pointCount; ++i) {
			for (int j = 0; j < numAttribs; ++j) {
				_pMesh->attribute(j)->SetPointMapEntry(draco::PointIndex(uint32_t(i)), draco::AttributeValueIndex(pData[i]));
			}
		}
	}
	break;
	}
}

int GLTFDracoExtension::_addAttribute(const GLTFAccessor* pAccessor, GLTFAttributeType attribType)
{
	const GLTFBufferView* pBufferView = pAccessor->bufferView();

	draco::DataBuffer* pBuffer = new draco::DataBuffer();
	buffers.push_back(pBuffer);

	pBuffer->Resize(pBufferView->byteLength());
	pBuffer->Write(0, pBufferView->data(), pBufferView->byteLength());

	GLTFAccessorType elementType = pAccessor->type();
	GLTFAccessorComponent componentType = pAccessor->component();

	draco::GeometryAttribute vertexAttribute;
	vertexAttribute.Init(
		_dracoAttributeType(attribType),
		pBuffer,
		(int8_t)elementType.componentCount(),
		_dracoComponentType(componentType),
		pAccessor->normalized(),
		pAccessor->elementByteSize(),
		0
	);
	cout << endl << "BUFFER" << endl;
	cout << "attribute type: " << vertexAttribute.attribute_type() << endl;
	cout << "data type: " << vertexAttribute.data_type() << endl;
	cout << "byte stride: " << vertexAttribute.byte_stride() << endl;
	cout << "num components: " << (size_t)vertexAttribute.num_components() << endl;
	cout << "element count: " << pAccessor->elementCount() << endl;
	cout << "is valid: " << vertexAttribute.IsValid() << endl;


	return _pMesh->AddAttribute(vertexAttribute, false, uint32_t(pAccessor->elementCount()));
}

