/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFTexture.h"

using namespace flow;


GLTFTexture::GLTFTexture(size_t index) :
	GLTFElement(index)
{
}

GLTFTexture::~GLTFTexture()
{
}

json GLTFTexture::toJSON() const
{
	return json({});
}
