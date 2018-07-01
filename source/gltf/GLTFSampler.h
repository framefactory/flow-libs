/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_SAMPLER_H
#define _FLOWLIBS_GLTF_SAMPLER_H

#include "GLTFElement.h"


namespace flow
{
	class GLTFSampler : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFSampler(size_t index);
		virtual ~GLTFSampler();

	public:
		virtual json toJSON() const;

	};
}

#endif // _FLOWLIBS_GLTF_SAMPLER_H
