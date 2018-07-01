/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFBuffer.h"
#include "GLTFBufferView.h"

using namespace flow;


GLTFBufferView::GLTFBufferView(size_t index, const GLTFBuffer* pBuffer) :
	GLTFElement(index),
	_pBuffer(pBuffer),
	_byteOffset(0),
	_byteLength(pBuffer->_byteLength),
	_target(Target::UNDEFINED)
{
}

void GLTFBufferView::setView(size_t offset, size_t length)
{
	_byteOffset = offset;
	_byteLength = length;
}

void GLTFBufferView::setTarget(Target target)
{
	_target = target;
}

json GLTFBufferView::toJSON() const
{
	auto result = json({
		{ "buffer", _pBuffer->index() },
		{ "byteOffset", _byteOffset },
		{ "byteLength", _byteLength }
	});

	if (_target != Target::UNDEFINED) {
		result["target"] = (size_t)_target;
	}

	return result;
}
