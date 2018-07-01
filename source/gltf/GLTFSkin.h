/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_SKIN_H
#define _FLOWLIBS_GLTF_SKIN_H

#include "GLTFElement.h"


namespace flow
{
	class GLTFSkin : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFSkin(size_t index);
		virtual ~GLTFSkin();

	public:
		virtual json toJSON() const;

	};
}

#endif // _FLOWLIBS_GLTF_SKIN_H
