/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFBuffer.h"

using namespace flow;
using std::string;


GLTFBuffer::GLTFBuffer(size_t index, const string& name /* = string{} */) :
	GLTFElement(index, name),
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

json GLTFBuffer::toJSON() const
{
	json result = GLTFElement::toJSON();

	result["byteLength"] = _byteLength;

	if (!_uri.empty()) {
		result["uri"] = _uri;
	}

	return result;
}
