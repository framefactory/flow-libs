/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_IMAGE_H
#define _FLOWLIBS_GLTF_IMAGE_H

#include "GLTFElement.h"

#include <string>


namespace flow
{
	class GLTFBufferView;

	enum class GLTFMimeType
	{
		IMAGE_JPEG,
		IMAGE_PNG
	};

	class GLTFImage : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFImage(size_t index, const std::string& name = std::string{});
		virtual ~GLTFImage() {}

	public:
		void setUri(const std::string& uri);
		void setBufferView(const GLTFBufferView* pBufferView, GLTFMimeType mimeType);

		const std::string& uri() const { return _uri; }
		const GLTFBufferView* bufferView() const { return _pBufferView; }
		const GLTFMimeType mimeType() const { return _mimeType; }

		virtual json toJSON() const;

	private:
		const char* _getMimeTypeName(GLTFMimeType mimeType) const;

		std::string _uri;
		const GLTFBufferView* _pBufferView;
		GLTFMimeType _mimeType;
	};
}

#endif // _FLOWLIBS_GLTF_IMAGE_H
