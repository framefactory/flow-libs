/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFTextureInfo.h"
#include "GLTFTexture.h"

using namespace flow;


GLTFTextureInfo::GLTFTextureInfo(const GLTFTexture* pTexture /* = nullptr */, size_t texCoord /* = 0 */) :
	_pTexture(pTexture),
	_texCoord(texCoord)
{
}

void GLTFTextureInfo::set(const GLTFTexture* pTexture, size_t texCoord /* = 0 */)
{
	_pTexture = pTexture;
	_texCoord = texCoord;
}

json GLTFTextureInfo::toJSON() const
{
	json result = GLTFElement::toJSON();

	result["index"] = _pTexture->index();

	if (_texCoord != 0) {
		result["texCoord"] = _texCoord;
	}

	return result;
}

GLTFNormalTextureInfo::GLTFNormalTextureInfo(const GLTFTexture* pTexture /* = nullptr */, size_t texCoord /* = 0 */, float scale /* = 1.0f */) :
	GLTFTextureInfo(pTexture, texCoord),
	_scale(scale)
{
}

void GLTFNormalTextureInfo::set(const GLTFTexture* pTexture, size_t texCoord /* = 0 */, float scale /* = 1.0f */)
{
	_pTexture = pTexture;
	_texCoord = texCoord;
	_scale = scale;
}

json GLTFNormalTextureInfo::toJSON() const
{
	json result = GLTFElement::toJSON();

	if (_scale != 1.0f) {
		result["scale"] = _scale;
	}

	return result;
}

GLTFOcclusionTextureInfo::GLTFOcclusionTextureInfo(GLTFTexture* pTexture /* = nullptr */, size_t texCoord /* = 0 */, float strength /* = 1.0f */) :
	GLTFTextureInfo(pTexture, texCoord),
	_strength(strength)
{
}

void GLTFOcclusionTextureInfo::set(const GLTFTexture* pTexture, size_t texCoord /* = 0 */, float strength /* = 1.0f */)
{
	_pTexture = pTexture;
	_texCoord = texCoord;
	_strength = strength;
}

json GLTFOcclusionTextureInfo::toJSON() const
{
	json result = GLTFElement::toJSON();

	if (_strength != 1.0f) {
		result["strength"] = _strength;
	}

	return result;
}