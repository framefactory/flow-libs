/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFSkin.h"

using namespace flow;
using std::string;

GLTFSkin::GLTFSkin(size_t index, const string& name /* = string{} */) :
	GLTFElement(index, name)
{
}

json GLTFSkin::toJSON() const
{
	json result = GLTFElement::toJSON();
	return result;
}
