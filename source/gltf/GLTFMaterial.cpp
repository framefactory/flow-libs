/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFMaterial.h"
#include "GLTFTexture.h"

using namespace flow;
using std::string;


const Vector3f GLTFMaterial::_DEFAULT_EMISSIVEFACTOR = Vector3f::zero;

GLTFMaterial::GLTFMaterial(size_t index, const string& name /* = string{} */) :
	GLTFMainElement(index, name),
	_pPbr(nullptr),
	_emissiveFactor(0.0f, 0.0f, 0.0f),
	_alphaMode(GLTFAlphaMode::OPAQUE),
	_alphaCutoff(0.5f),
	_doubleSided(false)
{
}

GLTFMaterial::~GLTFMaterial()
{
	F_SAFE_DELETE(_pPbr);
}

void GLTFMaterial::setPBRMetallicRoughness(const GLTFPBRMetallicRoughness& pbr)
{
	F_SAFE_DELETE(_pPbr);
	_pPbr = new GLTFPBRMetallicRoughness(pbr);
}

void GLTFMaterial::setNormalTexture(GLTFTexture* pTexture, size_t texCoord /* = 0 */, float scale /* = 1.0f */)
{
	_normalTextureInfo.set(pTexture, texCoord, scale);
}

void GLTFMaterial::setOcclusionTexture(GLTFTexture* pTexture, size_t texCoord /* = 0 */, float strength /* = 1.0f */)
{
	_occlusionTextureInfo.set(pTexture, texCoord, strength);
}

void GLTFMaterial::setEmissiveTexture(GLTFTexture* pTexture, size_t texCoord /* = 0 */)
{
	_emissiveTextureInfo.set(pTexture, texCoord);
}

void GLTFMaterial::setEmissiveFactor(const Vector3f& factor)
{
	_emissiveFactor = factor;
}

void GLTFMaterial::setAlphaMode(GLTFAlphaMode mode)
{
	_alphaMode = mode;
}

void GLTFMaterial::setAlphaCutoff(float cutoff)
{
	_alphaCutoff = cutoff;
}

void GLTFMaterial::setDoubleSided(bool doubleSided)
{
	_doubleSided = doubleSided;
}

json GLTFMaterial::toJSON() const
{
	json result = GLTFMainElement::toJSON();

	if (_pPbr) {
		result["pbrMetallicRoughness"] = _pPbr->toJSON();
	}
	if (_normalTextureInfo.texture()) {
		result["normalTexture"] = _normalTextureInfo.toJSON();
	}
	if (_occlusionTextureInfo.texture()) {
		result["occlusionTexture"] = _occlusionTextureInfo.toJSON();
	}
	if (_emissiveTextureInfo.texture()) {
		result["emissiveTexture"] = _emissiveTextureInfo.toJSON();
	}
	if (_emissiveFactor != _DEFAULT_EMISSIVEFACTOR) {
		result["emissiveFactor"] = _emissiveFactor.toJSON();
	}
	if (_alphaMode != GLTFAlphaMode::OPAQUE) {
		result["alphaMode"] = _getAlphaModeName(_alphaMode);
	}
	if (_alphaCutoff != 0.5f) {
		result["alphaCutoff"] = 0.5f;
	}
	if (_doubleSided) {
		result["doubleSided"] = _doubleSided;
	}

	return result;
}

const char* GLTFMaterial::_getAlphaModeName(GLTFAlphaMode mode) const
{
	switch (mode) {
	case GLTFAlphaMode::OPAQUE: return "OPAQUE";
	case GLTFAlphaMode::MASK: return "MASK";
	case GLTFAlphaMode::BLEND: return "BLEND";
	default: return "OPAQUE";
	}
}
