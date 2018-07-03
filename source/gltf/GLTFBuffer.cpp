/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFBuffer.h"
#include "GLTFBufferView.h"
#include "GLTFAccessor.h"
#include "GLTFObject.h"

#include <fstream>
#include <limits>

using namespace flow;
using std::string;
using std::ifstream;
using std::ios;
using std::numeric_limits;


static float _fMax = numeric_limits<float>::max();
static float _fMin = -_fMax;
static uint32_t _iMax = numeric_limits<uint32_t>::max();
static uint32_t _iMin = 0;
static Vector2f _v2Min{ _fMin, _fMin };
static Vector2f _v2Max{ _fMax, _fMax };
static Vector3f _v3Min{ _fMin, _fMin, _fMin };
static Vector3f _v3Max{ _fMax, _fMax, _fMax };


GLTFBuffer::GLTFBuffer(GLTFObject* pObject, size_t index, const string& name /* = string{} */) :
	GLTFMainElement(index, name),
	_bufferByteSize(0),
	_pObject(pObject),
	_byteLength(0)
{
}

void GLTFBuffer::setByteLength(size_t byteLength)
{
	_byteLength = byteLength;
}

void GLTFBuffer::setUri(const string& uri)
{
	_uri = uri;
}

GLTFBufferView* GLTFBuffer::addImage(const string& imageFile)
{
	std::ifstream stream(imageFile, ios::in | ios::ate | ios::binary);
	size_t byteLength = (size_t)stream.tellg();

	size_t byteStart = _bufferByteSize;
	_bufferByteSize += byteLength;
	_resizeBuffer(_bufferByteSize);

	char* pDest = ((char*)_buffer.data()) + byteStart;
	stream.seekg(0);
	stream.read(pDest, byteLength);

	auto pBufferView = _pObject->createBufferView(this);
	pBufferView->setView(byteStart, byteLength);
	return pBufferView;
}

GLTFBufferView* GLTFBuffer::addData(const char* pData, size_t byteLength)
{
	size_t byteStart = _bufferByteSize;
	_bufferByteSize += byteLength;
	_resizeBuffer(_bufferByteSize);

	char* pDest = ((char*)_buffer.data()) + byteStart;
	std::memcpy(pDest, pData, byteLength);

	auto pBufferView = _pObject->createBufferView(this);
	pBufferView->setView(byteStart, byteLength);
	return pBufferView;
}

GLTFAccessor* GLTFBuffer::addData(const Vector3f* pData, size_t vertexCount)
{
	const char* pRawData = (char*)pData;
	size_t byteLength = vertexCount * sizeof(Vector3f);

	auto pBufferView = addData(pRawData, byteLength);
	pBufferView->setTarget(GLTFBufferTarget::ARRAY_BUFFER);

	auto pAccessor = _pObject->createAccessor(pBufferView);
	pAccessor->setType(GLTFAccessorType::VEC3, GLTFAccessorComponent::FLOAT);
	pAccessor->setRange(vertexCount, 0);

	Vector3f vMax = _v3Min;
	Vector3f vMin = _v3Max;
	_getMinMax(pData, vertexCount, &vMin, &vMax);
	pAccessor->setMin({ vMin.x, vMin.y, vMin.z });
	pAccessor->setMax({ vMax.x, vMax.y, vMax.z });

	return pAccessor;
}

GLTFAccessor* GLTFBuffer::addData(const Vector2f* pData, size_t vertexCount)
{
	const char* pRawData = (char*)pData;
	size_t byteLength = vertexCount * sizeof(Vector2f);

	auto pBufferView = addData(pRawData, byteLength);
	pBufferView->setTarget(GLTFBufferTarget::ARRAY_BUFFER);

	auto pAccessor = _pObject->createAccessor(pBufferView);
	pAccessor->setType(GLTFAccessorType::VEC2, GLTFAccessorComponent::FLOAT);
	pAccessor->setRange(vertexCount, 0);

	Vector2f vMax = _v2Min;
	Vector2f vMin = _v2Max;
	_getMinMax(pData, vertexCount, &vMin, &vMax);
	pAccessor->setMin({ vMin.x, vMin.y });
	pAccessor->setMax({ vMax.x, vMax.y });

	return pAccessor;
}

GLTFAccessor* GLTFBuffer::addData(const uint32_t* pData, size_t elementCount)
{
	const char* pRawData = (char*)pData;
	size_t byteLength = elementCount * sizeof(uint32_t);

	auto pBufferView = addData(pRawData, byteLength);
	pBufferView->setTarget(GLTFBufferTarget::ELEMENT_ARRAY_BUFFER);

	auto pAccessor = _pObject->createAccessor(pBufferView);
	pAccessor->setType(GLTFAccessorType::SCALAR, GLTFAccessorComponent::UNSIGNED_INT);
	pAccessor->setRange(elementCount, 0);

	uint32_t iMax = _iMin;
	uint32_t iMin = _iMax;
	_getMinMax(pData, elementCount, &iMin, &iMax);
	pAccessor->setMin({ (double)iMin });
	pAccessor->setMax({ (double)iMax });

	return pAccessor;
}

json GLTFBuffer::toJSON() const
{
	json result = GLTFMainElement::toJSON();

	result["byteLength"] = _byteLength;

	if (!_uri.empty()) {
		result["uri"] = _uri;
	}

	return result;
}

void GLTFBuffer::_resizeBuffer(size_t byteSize)
{
	size_t size = byteSize / sizeof(size_t);
	_buffer.resize(size);
	_bufferByteSize = byteSize;
}