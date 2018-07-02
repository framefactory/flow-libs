/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFMaterial.h"

using namespace flow;
using std::string;


GLTFMaterial::GLTFMaterial(size_t index, const string& name /* = string{} */) :
	GLTFElement(index, name)
{
}

json GLTFMaterial::toJSON() const
{
	json result = GLTFElement::toJSON();
	return result;
}
