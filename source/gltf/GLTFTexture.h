/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_TEXTURE_H
#define _FLOWLIBS_GLTF_TEXTURE_H

#include "GLTFElement.h"


namespace flow
{
	class GLTFTexture : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFTexture(size_t index);
		virtual ~GLTFTexture();

	public:
		virtual json toJSON() const;

	};
}

#endif // _FLOWLIBS_GLTF_TEXTURE_H
