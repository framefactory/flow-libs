/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFPBRMetallicRoughness.h"

using namespace flow;


const Vector4f GLTFPBRMetallicRoughness::_DEFAULT_BASECOLORFACTOR = Vector4f::ones;

GLTFPBRMetallicRoughness::GLTFPBRMetallicRoughness() :
	_baseColorFactor(1.0f, 1.0f, 1.0f, 1.0f),
	_metallicFactor(1.0f),
	_roughnessFactor(1.0f)
{
}

void GLTFPBRMetallicRoughness::setBaseColorFactor(const Vector4f& factor)
{
	_baseColorFactor = factor;
}

void GLTFPBRMetallicRoughness::setBaseColorTexture(GLTFTexture* pTexture, size_t texCoords /* = 0 */)
{
	_baseColorTexture.set(pTexture, texCoords);
}

void GLTFPBRMetallicRoughness::setMetallicFactor(float factor)
{
	_metallicFactor = factor;
}

void GLTFPBRMetallicRoughness::setRoughnessFactor(float factor)
{
	_roughnessFactor = factor;
}

void GLTFPBRMetallicRoughness::setMetallicRoughnessTexture(GLTFTexture* pTexture, size_t texCoords /* = 0 */)
{
	_metallicRoughnessTexture.set(pTexture, texCoords);
}

json GLTFPBRMetallicRoughness::toJSON() const
{
	json result = GLTFElement::toJSON();

	if (_baseColorFactor != _DEFAULT_BASECOLORFACTOR) {
		result["baseColorFactor"] = _baseColorFactor.toJSON();
	}
	if (_baseColorTexture.texture()) {
		result["baseColorTexture"] = _baseColorTexture.toJSON();
	}
	if (_metallicFactor != 1.0f) {
		result["metallicFactor"] = _metallicFactor;
	}
	if (_roughnessFactor != 1.0f) {
		result["roughnessFactor"] = _roughnessFactor;
	}
	if (_metallicRoughnessTexture.texture()) {
		result["metallicRoughnessTexture"] = _metallicRoughnessTexture.toJSON();
	}

	return result;
}
