/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFSampler.h"

using namespace flow;


GLTFSampler::GLTFSampler(size_t index) :
	GLTFElement(index)
{
}

GLTFSampler::~GLTFSampler()
{
}

json GLTFSampler::toJSON() const
{
	return json({});
}
