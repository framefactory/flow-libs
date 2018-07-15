/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFAccessor.h"

#include "GLTFBuffer.h"
#include "GLTFBufferView.h"

using namespace flow;
using std::string;
using std::vector;


GLTFAccessor::GLTFAccessor(size_t index, GLTFAccessorType type, string& name /* = std::string{} */) :
	GLTFMainElement(index, name),
	_pBufferView(nullptr),
	_type(type),
	_normalized(false),
	_count(0),
	_byteOffset(0),
	_byteStride(0)
{
}

void GLTFAccessor::setNormalized(bool normalized)
{
	_normalized = normalized;
}

void GLTFAccessor::setInterleaved(size_t byteOffset, size_t byteStride)
{
	// if offset is given, stride must be given as well
	F_ASSERT((byteStride == 0 && byteOffset == 0) || byteStride != 0);

	_byteOffset = _byteOffset;
	_byteStride = _byteStride;
}

void GLTFAccessor::addData(GLTFBuffer* pBuffer, const char* pData, size_t byteLength, GLTFBufferViewTarget target)
{
	_pBufferView = pBuffer->addData(pData, byteLength);
	_pBufferView->setTarget(target);
}

char* GLTFAccessor::allocateData(GLTFBuffer* pBuffer, size_t byteLength, GLTFBufferViewTarget target)
{
	_pBufferView = pBuffer->allocate(byteLength);
	_pBufferView->setTarget(target);

	return _pBufferView->data();
}

void GLTFAccessor::setElementCount(size_t elementCount)
{
	_count = elementCount;
}

const char* GLTFAccessor::data() const
{
	if (!_pBufferView) {
		return nullptr;
	}

	return _pBufferView->data();
}

json GLTFAccessor::toJSON() const
{
	json result = GLTFMainElement::toJSON();

	result["type"] = _type.name();
	result["count"] = _count;

	if (_pBufferView) {
		result["bufferView"] = _pBufferView->index();
	}
	if (_byteOffset > 0) {
		result["byteOffset"] = _byteOffset;
	}
	if (_byteStride > 0) {
		result["byteStride"] = _byteStride;
	}
	if (_normalized) {
		result["normalized"] = true;
	}

	return result;
}
