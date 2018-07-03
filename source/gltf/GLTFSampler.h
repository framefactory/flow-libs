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

#include <string>


namespace flow
{
	enum class GLTFMagFilter
	{
		NEAREST = 9728,
		LINEAR = 9729
	};

	enum class GLTFMinFilter
	{
		NEAREST = 9728,
		LINEAR = 9729,
		NEAREST_MIPMAP_NEAREST = 9984,
		LINEAR_MIPMAP_NEAREST = 9985,
		NEAREST_MIPMAP_LINEAR = 9986,
		LINEAR_MIPMAP_LINEAR = 9987
	};

	enum class GLTFWrapMode
	{
		REPEAT = 10497,
		CLAMP_TO_EDGE = 33071,
		MIRRORED_REPEAT = 33648
	};

	class GLTFSampler : public GLTFMainElement
	{
		friend class GLTFObject;

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
