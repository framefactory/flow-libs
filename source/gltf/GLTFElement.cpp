/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFElement.h"

using namespace flow;
using std::string;


GLTFElement::GLTFElement(size_t index, const string& name) :
	_index(index),
	_name(name)
{
}

void GLTFElement::setName(const std::string& name)
{
	_name = name;
}

void GLTFElement::addExtension(std::string& prop, const json& jsonData)
{
	_extensions[prop] = jsonData;
}

void GLTFElement::setExtras(const json& jsonData)
{
	_extras = jsonData;
}

json GLTFElement::toJSON() const
{
	json result;

	if (!_name.empty()) {
		result["name"] = _name;
	}
	if (!_extensions.empty()) {
		result["extensions"] = _extensions;
	}
	if (!_extras.empty()) {
		result["extras"] = _extras;
	}

	return result;
}

string GLTFElement::toString(int indent /* = -1 */) const
{
	return toJSON().dump(indent);
}
