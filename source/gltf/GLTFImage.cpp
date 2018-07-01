/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFImage.h"

using namespace flow;


GLTFImage::GLTFImage(size_t index) :
	GLTFElement(index)
{
}

GLTFImage::~GLTFImage()
{
}

json GLTFImage::toJSON() const
{
	return json({});
}
