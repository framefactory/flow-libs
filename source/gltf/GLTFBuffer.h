/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_BUFFER_H
#define _FLOWLIBS_GLTF_BUFFER_H

#include "GLTFElement.h"
#include <string>


namespace flow
{
	class GLTFBuffer : public GLTFElement
	{
		friend class GLTFAsset;
		friend class GLTFBufferView;

	protected:
		GLTFBuffer(size_t index, size_t byteLength);
		virtual ~GLTFBuffer() {};

	public:
		void setUri(const std::string& uri);

		virtual json toJSON() const;

	private:
		size_t _byteLength;
		std::string _uri;
	};
}

#endif // _FLOWLIBS_GLTF_BUFFER_H
