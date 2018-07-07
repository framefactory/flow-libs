/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_MATERIAL_H
#define _FLOWLIBS_GLTF_MATERIAL_H

#include "library.h"
#include "GLTFMainElement.h"
#include "GLTFConstants.h"

#include "GLTFTextureInfo.h"
#include "GLTFPBRMetallicRoughness.h"

#include "../math/Vector3T.h"

#include <string>


namespace flow
{
	class F_GLTF_EXPORT GLTFMaterial : public GLTFMainElement
	{
		friend class GLTFAsset;

	protected:
		GLTFMaterial(size_t index, const std::string& name = std::string{});
		virtual ~GLTFMaterial();

	public:
		void setPBRMetallicRoughness(const GLTFPBRMetallicRoughness& pbr);
		void setNormalTexture(GLTFTexture* pTexture, size_t texCoord = 0, float scale = 1.0f);
		void setOcclusionTexture(GLTFTexture* pTexture, size_t texCoord = 0, float strength = 1.0f);
		void setEmissiveTexture(GLTFTexture* pTexture, size_t texCoord = 0);
		void setEmissiveFactor(const Vector3f& factor);
		void setAlphaMode(GLTFAlphaMode mode);
		void setAlphaCutoff(float cutoff);
		void setDoubleSided(bool doubleSided);

		virtual json toJSON() const;

	private:
		const char* _getAlphaModeName(GLTFAlphaMode mode) const;
		
		static const Vector3f _DEFAULT_EMISSIVEFACTOR;

		GLTFPBRMetallicRoughness* _pPbr;
		GLTFNormalTextureInfo _normalTextureInfo;
		GLTFOcclusionTextureInfo _occlusionTextureInfo;
		GLTFTextureInfo _emissiveTextureInfo;
		Vector3f _emissiveFactor;
		GLTFAlphaMode _alphaMode;
		float _alphaCutoff;
		bool _doubleSided;
	};
}

#endif // _FLOWLIBS_GLTF_MATERIAL_H
