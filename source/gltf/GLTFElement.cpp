/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFElement.h"
#include "GLTFExtension.h"

using namespace flow;
using std::string;


void GLTFElement::addExtension(const GLTFExtension* pExtension)
{
	_extensions.push_back(pExtension);
}

void GLTFElement::setExtras(const json& jsonData)
{
	_extras = jsonData;
}

json GLTFElement::toJSON() const
{
	json result;

	if (!_extensions.empty()) {
		json extensions;
		for (size_t i = 0; i < _extensions.size(); ++i) {
			extensions[_extensions[i]->name()] = _extensions[i]->toJSON();
		}
		result["extensions"] = extensions;
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
