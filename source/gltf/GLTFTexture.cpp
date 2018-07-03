/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFTexture.h"
#include "GLTFImage.h"
#include "GLTFSampler.h"

using namespace flow;
using std::string;


GLTFTexture::GLTFTexture(size_t index, const string& name /* = std::string{} */) :
	GLTFMainElement(index, name),
	_pImage(nullptr),
	_pSampler(nullptr)
{
}

void GLTFTexture::setSource(const GLTFImage* pImage, const GLTFSampler* pSampler /* = nullptr */)
{
	_pImage = pImage;
	_pSampler = pSampler;
}

json GLTFTexture::toJSON() const
{
	json result = GLTFMainElement::toJSON();

	if (_pImage) {
		result["source"] = _pImage->index();
	}
	if (_pSampler) {
		result["sampler"] = _pSampler->index();
	}

	return result;
}
