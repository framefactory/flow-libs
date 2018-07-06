/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_ACCESSORT_H
#define _FLOWLIBS_GLTF_ACCESSORT_H

#include "library.h"
#include "GLTFAccessor.h"

namespace flow
{
	template <typename T, size_t N>
	class GLTFAccessorT : public GLTFAccessor
	{
		GLTFAccessorT<float, 2>::GLTFAccessorT();
		GLTFAccessorT<float, 2>::GLTFAccessorT();
	};

	typedef GLTFAccessorT<float, 2> GLTFAccessor2f;
	typedef GLTFAccessorT<float, 3> GLTFAccessor3f;
	typedef GLTFAccessorT<uint16_t, 1> GLTFAccessorIndex16;
	typedef GLTFAccessorT<uint32_t, 1> GLTFAccessorIndex32;

}

#endif // _FLOWLIBS_GLTF_ACCESSORT_H