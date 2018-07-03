/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_TEXTURE_H
#define _FLOWLIBS_GLTF_TEXTURE_H

#include "library.h"
#include "GLTFMainElement.h"

#include <string>


namespace flow
{
	class GLTFImage;
	class GLTFSampler;

	class GLTFTexture : public GLTFMainElement
	{
		friend class GLTFObject;

	protected:
		GLTFTexture(size_t index, const std::string& name = std::string{});
		virtual ~GLTFTexture() { }

	public:
		void setSource(const GLTFImage* pImage, const GLTFSampler* pSampler = nullptr);

		const GLTFImage* image() const { return _pImage; }
		const GLTFSampler* sampler() const { return _pSampler; }
		
		virtual json toJSON() const;

	private:
		const GLTFImage* _pImage;
		const GLTFSampler* _pSampler;
	};
}

#endif // _FLOWLIBS_GLTF_TEXTURE_H
