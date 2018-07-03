/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFSampler.h"

using namespace flow;
using std::string;


GLTFSampler::GLTFSampler(size_t index, const string& name /* = std::string{} */) :
	GLTFMainElement(index, name),
	_magFilter(GLTFMagFilter::LINEAR),
	_minFilter(GLTFMinFilter::LINEAR),
	_wrapS(GLTFWrapMode::REPEAT),
	_wrapT(GLTFWrapMode::REPEAT)
{
}

void GLTFSampler::setFilter(GLTFMagFilter magFilter, GLTFMinFilter minFilter)
{
	_magFilter = magFilter;
	_minFilter = minFilter;
}

void GLTFSampler::setWrapMode(GLTFWrapMode wrapS, GLTFWrapMode wrapT)
{
	_wrapS = wrapS;
	_wrapT = wrapT;
}

json GLTFSampler::toJSON() const
{
	json result = GLTFMainElement::toJSON();

	result["magFilter"] = (int)_magFilter;
	result["minFilter"] = (int)_minFilter;
	result["wrapS"] = (int)_wrapS;
	result["wrapT"] = (int)_wrapT;

	return result;
}
