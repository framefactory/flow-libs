/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFAnimation.h"

using namespace flow;
using std::string;


GLTFAnimation::GLTFAnimation(size_t index, const string& name /* = std::string */) :
	GLTFMainElement(index, name)
{
}

json GLTFAnimation::toJSON() const
{
	json result = GLTFMainElement::toJSON();

	return result;
}