/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_BUFFER_H
#define _FLOWLIBS_GLTF_BUFFER_H

#include "library.h"
#include "GLTFMainElement.h"
#include "GLTFAccessor.h"
#include "GLTFAsset.h"

#include "../math/Vector2T.h"
#include "../math/Vector3T.h"

#include <string>
#include <vector>


namespace flow
{
	class GLTFBufferView;

	class F_GLTF_EXPORT GLTFBuffer : public GLTFMainElement
	{
		friend class GLTFAsset;

	protected:
		GLTFBuffer(GLTFAsset* pAsset, size_t index, const std::string& name = std::string{});
		virtual ~GLTFBuffer() { };

	public:
		GLTFBufferView* addData(const char* pData, size_t byteLength, bool align = true);
		GLTFBufferView* addImage(const std::string& imageFilePath);
		GLTFBufferView* allocate(size_t byteLength, bool align = true);

		void setUri(const std::string& uri);
		bool save(const std::string& bufferFilePath);

		char* data() { return _buffer.data(); }
		const char* data() const { return _buffer.data(); }

		size_t byteLength() const { return _buffer.size(); }
		const std::string& uri() const { return _uri; }

		virtual json toJSON() const;

	private:
		GLTFAsset * _pAsset;
		std::vector<char> _buffer;

		std::string _uri;
	};
}

#endif // _FLOWLIBS_GLTF_BUFFER_H
