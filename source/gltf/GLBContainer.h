/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_GLBCONTAINER_H
#define _FLOWLIBS_GLTF_GLBCONTAINER_H

#include "library.h"
#include <string>


namespace flow
{
	class GLTFAsset;

	class F_GLTF_EXPORT GLBContainer
	{
	public:
		GLBContainer(const GLTFAsset* pAsset);
		virtual ~GLBContainer() {};

		bool save(const std::string& fileName) const;

	private:
		uint32_t _spaces = 0x20202020;
		uint32_t _null = 0;

		mutable struct
		{
			uint32_t magic = 0x46546C67;
			uint32_t version = 2;
			uint32_t length = 0;
		} _glbHeader;

		mutable struct
		{
			uint32_t length = 0;
			uint32_t type = 0x4E4F534A;
		} _jsonChunkHeader;

		mutable struct
		{
			uint32_t length = 0;
			uint32_t type = 0x004E4942;
		} _binChunkHeader;

		const GLTFAsset* _pAsset;
	};
}

#endif // _FLOWLIBS_GLTF_GLBCONTAINER_H
