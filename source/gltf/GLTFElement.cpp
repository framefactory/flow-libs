/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFElement.h"

using namespace flow;
using std::string;


void GLTFElement::addExtension(string& prop, const json& jsonData)
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
