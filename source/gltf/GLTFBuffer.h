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

#include "../math/Vector2T.h"
#include "../math/Vector3T.h"

#include <string>
#include <vector>


namespace flow
{
	class GLTFBufferView;

	class GLTFBuffer : public GLTFMainElement
	{
		friend class GLTFObject;

	protected:
		GLTFBuffer(GLTFObject* pObject, size_t index, const std::string& name = std::string{});
		virtual ~GLTFBuffer() { };

	public:
		void setByteLength(const size_t byteLength);
		void setUri(const std::string& uri);

		size_t byteLength() const { return _byteLength; }
		const std::string& uri() const { return _uri; }

		virtual json toJSON() const;

	private:
		void _resizeBuffer(size_t byteSize);

		template<typename T>
		void _getMinMax(const T* pData, size_t count, T* pMin, T* pMax);

		std::vector<size_t> _buffer;

		GLTFObject* _pObject;
		size_t _byteLength;
		std::string _uri;
	};
}

#endif // _FLOWLIBS_GLTF_BUFFER_H
