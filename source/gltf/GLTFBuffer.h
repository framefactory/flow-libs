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
	class GLTFBufferView;

	class GLTFBuffer : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFBuffer(size_t index, const std::string& name = std::string{});
		virtual ~GLTFBuffer() { };

	public:
		void setByteLength(size_t byteLength);
		void setUri(const std::string& uri);

		size_t byteLength() const { return _byteLength; }
		const std::string& uri() const { return _uri; }

		virtual json toJSON() const;

	private:
		size_t _byteLength;
		std::string _uri;
	};
}

#endif // _FLOWLIBS_GLTF_BUFFER_H
