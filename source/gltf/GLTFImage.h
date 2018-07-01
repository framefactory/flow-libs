/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_IMAGE_H
#define _FLOWLIBS_GLTF_IMAGE_H

#include "GLTFElement.h"


namespace flow
{
	class GLTFImage : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFImage(size_t index);
		virtual ~GLTFImage();

	public:
		virtual json toJSON() const;

	};
}

#endif // _FLOWLIBS_GLTF_IMAGE_H
