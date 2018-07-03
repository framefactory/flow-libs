/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFMainElement.h"

using namespace flow;
using std::string;


GLTFMainElement::GLTFMainElement(size_t index, const string& name /* = string{} */) :
	GLTFElement(),
	_index(index),
	_name(name)
{
}

void GLTFMainElement::setName(const string& name)
{
	_name = name;
}

json GLTFMainElement::toJSON() const
{
	json result = GLTFElement::toJSON();

	if (!_name.empty()) {
		result["name"] = _name;
	}

	return result;
}