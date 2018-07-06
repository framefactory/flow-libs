/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFBuffer.h"
#include "GLTFBufferView.h"

using namespace flow;
using std::string;


GLTFBufferView::GLTFBufferView(size_t index, const string& name /* = std::string{} */) :
	GLTFMainElement(index, name),
	_pBuffer(nullptr),
	_byteOffset(0),
	_byteLength(0),
	_byteStride(0),
	_target(GLTFBufferViewTarget::ARRAY_BUFFER)
{
}

void GLTFBufferView::setTarget(GLTFBufferViewTarget target)
{
	_target = target;
}

char* GLTFBufferView::data() const
{
	if (!_pBuffer) {
		return nullptr;
	}

	return _pBuffer->data() + _byteOffset;
}

json GLTFBufferView::toJSON() const
{
	json result = GLTFMainElement::toJSON();

	if (!_pBuffer) {
		throw std::exception("GLTFBufferView: buffer not set");
	}
	if (_byteLength == 0) {
		throw std::exception("GLTFBufferView: byteLength not set");
	}
	
	result["buffer"] = _pBuffer->index();
	result["byteLength"] = _byteLength;

	if (_byteOffset > 0) {
		result["byteOffset"] = _byteOffset;
	}
	if (_byteStride > 0) {
		result["byteStride"] = _byteStride;
	}
	if (_target != GLTFBufferViewTarget::UNDEFINED) {
		result["target"] = (int)_target;
	}

	return result;
}

void GLTFBufferView::_set(GLTFBuffer* pBuffer, size_t byteOffset, size_t byteLength, size_t byteStride /* = 0 */)
{
	_pBuffer = pBuffer;
	_byteOffset = byteOffset;
	_byteLength = byteLength;
	_byteStride = byteStride;
}
