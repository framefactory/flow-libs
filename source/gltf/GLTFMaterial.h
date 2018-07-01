/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_MATERIAL_H
#define _FLOWLIBS_GLTF_MATERIAL_H

#include "GLTFElement.h"


namespace flow
{
	class GLTFMaterial : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFMaterial(size_t index);
		virtual ~GLTFMaterial();

	public:
		virtual json toJSON() const;

	};
}

#endif // _FLOWLIBS_GLTF_MATERIAL_H
