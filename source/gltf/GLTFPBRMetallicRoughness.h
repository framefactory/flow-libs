/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_PBRMETALLICROUGHNESS_H
#define _FLOWLIBS_GLTF_PBRMETALLICROUGHNESS_H

#include "library.h"
#include "GLTFElement.h"
#include "GLTFTextureInfo.h"

#include "../math/Vector4T.h"


namespace flow
{
	class GLTFTexture;

	class F_GLTF_EXPORT GLTFPBRMetallicRoughness : public GLTFElement
	{
	public:
		GLTFPBRMetallicRoughness();
		virtual ~GLTFPBRMetallicRoughness() { }

		void setBaseColorFactor(const Vector4f& factor);
		void setBaseColorTexture(GLTFTexture* pTexture, size_t texCoords = 0);
		void setMetallicFactor(float factor);
		void setRoughnessFactor(float factor);
		void setMetallicRoughnessTexture(GLTFTexture* pTexture, size_t texCoords = 0);

		const Vector4f& baseColorFactor() const { return _baseColorFactor; }
		const GLTFTextureInfo& baseColorTexture() const { return _baseColorTexture; }
		float metallicFactor() const { return _metallicFactor; }
		float roughnessFactor() const { return _roughnessFactor; }
		const GLTFTextureInfo& metallicRoughnessTexture() const { return _metallicRoughnessTexture; }

		virtual json toJSON() const;

	private:
		static const Vector4f _DEFAULT_BASECOLORFACTOR;

		Vector4f _baseColorFactor;
		GLTFTextureInfo _baseColorTexture;
		float _metallicFactor;
		float _roughnessFactor;
		GLTFTextureInfo _metallicRoughnessTexture;
	};
}

#endif // _FLOWLIBS_GLTF_PBRMETALLICROUGHNESS_H