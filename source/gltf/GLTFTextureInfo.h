/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_TEXTUREINFO_H
#define _FLOWLIBS_GLTF_TEXTUREINFO_H

#include "library.h"
#include "GLTFElement.h"


namespace flow
{
	class GLTFTexture;

	class F_GLTF_EXPORT GLTFTextureInfo : public GLTFElement
	{
	public:
		GLTFTextureInfo(const GLTFTexture* pTexture = nullptr, size_t texCoord = 0);
		virtual ~GLTFTextureInfo() {}

		void set(const GLTFTexture* pTexture, size_t texCoord = 0);

		const GLTFTexture* texture() const { return _pTexture; }
		size_t texCoord() const { return _texCoord; }

		virtual json toJSON() const;

	protected:
		const GLTFTexture* _pTexture;
		size_t _texCoord;
	};

	class F_GLTF_EXPORT GLTFNormalTextureInfo : public GLTFTextureInfo
	{
	public:
		GLTFNormalTextureInfo(const GLTFTexture* pTexture = nullptr, size_t texCoord = 0, float scale = 1.0f);
		virtual ~GLTFNormalTextureInfo() {}

		void set(const GLTFTexture* pTexture, size_t texCoord = 0, float scale = 1.0f);
		float scale() const { return _scale; }

		virtual json toJSON() const;

	protected:
		float _scale;
	};

	class F_GLTF_EXPORT GLTFOcclusionTextureInfo : public GLTFTextureInfo
	{
	public:
		GLTFOcclusionTextureInfo(GLTFTexture* pTexture = nullptr, size_t texCoord = 0, float strength = 1.0f);
		virtual ~GLTFOcclusionTextureInfo() {}

		void set(const GLTFTexture* pTexture, size_t texCoord = 0, float strength = 1.0f);
		float strength() const { return _strength; }

		virtual json toJSON() const;

	protected:
		float _strength;
	};
}

# endif // _FLOWLIBS_GLTF_TEXTUREINFO_H