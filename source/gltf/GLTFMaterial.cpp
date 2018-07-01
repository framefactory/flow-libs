/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFMaterial.h"

using namespace flow;


GLTFMaterial::GLTFMaterial(size_t index) :
	GLTFElement(index)
{
}

GLTFMaterial::~GLTFMaterial()
{
}

json GLTFMaterial::toJSON() const
{
	return json({});
}
