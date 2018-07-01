/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFSkin.h"

using namespace flow;


GLTFSkin::GLTFSkin(size_t index) :
	GLTFElement(index)
{
}

GLTFSkin::~GLTFSkin()
{
}

json GLTFSkin::toJSON() const
{
	return json({});
}
