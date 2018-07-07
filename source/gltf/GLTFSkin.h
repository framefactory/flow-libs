/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_SKIN_H
#define _FLOWLIBS_GLTF_SKIN_H

#include "library.h"
#include "GLTFMainElement.h"

#include <string>


namespace flow
{
	class F_GLTF_EXPORT GLTFSkin : public GLTFMainElement
	{
		friend class GLTFAsset;

	protected:
		GLTFSkin(size_t index, const std::string& name = std::string{});
		virtual ~GLTFSkin() { }

	public:
		virtual json toJSON() const;

	};
}

#endif // _FLOWLIBS_GLTF_SKIN_H
