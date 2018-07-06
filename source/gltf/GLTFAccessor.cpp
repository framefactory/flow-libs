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

char* GLTFAccessor::_allocate(GLTFBuffer* pBuffer, size_t byteLength)
{
	_pBufferView = pBuffer->allocate(byteLength);
	return _pBufferView->data();
}

void GLTFAccessor::_setData(GLTFBuffer* pBuffer, const char* pData, size_t byteLength)
{
	_pBufferView = pBuffer->addData(pData, byteLength);
}

const char* GLTFAccessor::_getData() const
{
	if (!_pBufferView) {
		return nullptr;
	}

	return _pBufferView->data();
}