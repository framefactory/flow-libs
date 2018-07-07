/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_ANIMATION_H
#define _FLOWLIBS_GLTF_ANIMATION_H

#include "library.h"
#include "GLTFMainElement.h"
#include "GLTFConstants.h"

#include <string>


namespace flow
{
	class F_GLTF_EXPORT GLTFAnimation : public GLTFMainElement
	{
		friend class GLTFAsset;

	protected:
		GLTFAnimation(size_t index, const std::string& name = std::string{});
		virtual ~GLTFAnimation() {}

	public:
		virtual json toJSON() const;

	private:
	};
}

#endif // _FLOWLIBS_GLTF_ANIMATION_H
