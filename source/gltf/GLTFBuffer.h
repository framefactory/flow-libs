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
#include "../math/Vector2T.h"
#include "../math/Vector3T.h"

#include <string>
#include <vector>


namespace flow
{
	class GLTFBufferView;
	class GLTFAccessor;

	class GLTFBuffer : public GLTFMainElement
	{
		friend class GLTFObject;

	protected:
		GLTFBuffer(GLTFObject* pObject, size_t index, const std::string& name = std::string{});
		virtual ~GLTFBuffer() { };

	public:
		void setByteLength(size_t byteLength);
		void setUri(const std::string& uri);

		GLTFBufferView* addImage(const std::string& imageFile);
		GLTFBufferView* addData(const char* pData, size_t byteLength);

		GLTFAccessor* addData(const Vector3f* pData, size_t vertexCount);
		GLTFAccessor* addData(const Vector2f* pData, size_t vertexCount);
		GLTFAccessor* addData(const uint32_t* pData, size_t elementCount);

		size_t byteLength() const { return _byteLength; }
		const std::string& uri() const { return _uri; }

		virtual json toJSON() const;

	private:
		void _resizeBuffer(size_t byteSize);

		template<typename T>
		void _getMinMax(const T* pData, size_t count, T* pMin, T* pMax);

		std::vector<size_t> _buffer;
		size_t _bufferByteSize;

		GLTFObject* _pObject;
		size_t _byteLength;
		std::string _uri;
	};

	template<typename T>
	void GLTFBuffer::_getMinMax(const T* pData, size_t count, T* pMin, T* pMax)
	{
		for (size_t i = 0; i < count; ++i) {
			*pMin = flow::min(*pMin, pData[i]);
			*pMax = flow::max(*pMax, pData[i]);
		}
	}
}

#endif // _FLOWLIBS_GLTF_BUFFER_H
