/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFBuffer.h"

using namespace flow;


GLTFBuffer::GLTFBuffer(size_t index, size_t byteLength) :
	GLTFElement(index),
	_byteLength(byteLength)
{
}

void GLTFBuffer::setUri(const std::string& uri)
{
	_uri = uri;
}

json GLTFBuffer::toJSON() const
{
	return json({
		{ "byteLength", _byteLength },
		{ "uri", _uri }
	});
}
