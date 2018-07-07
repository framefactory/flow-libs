/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_SAMPLER_H
#define _FLOWLIBS_GLTF_SAMPLER_H

#include "library.h"
#include "GLTFMainElement.h"
#include "GLTFConstants.h"

#include <string>


namespace flow
{
	class F_GLTF_EXPORT GLTFSampler : public GLTFMainElement
	{
		friend class GLTFAsset;

	protected:
		GLTFSampler(size_t index, const std::string& name = std::string{});
		virtual ~GLTFSampler() { }

	public:
		void setFilter(GLTFMagFilter magFilter, GLTFMinFilter minFilter);
		void setWrapMode(GLTFWrapMode wrapS, GLTFWrapMode wrapT);

		GLTFMagFilter magFilter() const { return _magFilter; }
		GLTFMinFilter minFilter() const { return _minFilter; }
		GLTFWrapMode wrapS() const { return _wrapS; }
		GLTFWrapMode wrapT() const { return _wrapT; }

		virtual json toJSON() const;

	private:
		GLTFMagFilter _magFilter;
		GLTFMinFilter _minFilter;
		GLTFWrapMode _wrapS;
		GLTFWrapMode _wrapT;
	};
}

#endif // _FLOWLIBS_GLTF_SAMPLER_H
