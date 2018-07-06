/**
 * Flow Libs - GLTF
 *
 * @author Ralph Wiedemeier <ralph@framefactory.io>
 * @copyright (c) 2018 Frame Factory GmbH.
 */
 
#ifndef _FLOWLIBS_GLTF_ACCESSOR_H
#define _FLOWLIBS_GLTF_ACCESSOR_H
 
#include "library.h"
#include "GLTFMainElement.h"
#include "GLTFConstants.h"

#include "../math/Vector2T.h"
#include "../math/Vector3T.h"
#include "../math/Vector4T.h"

#include <string>
#include <vector>


namespace flow
{
	class GLTFBufferView;
	class GLTFBuffer;

	class F_GLTF_EXPORT GLTFAccessor : public GLTFMainElement
	{
	protected:
		GLTFAccessor(size_t index, GLTFAccessorType type, std::string& name);

	public:
		virtual ~GLTFAccessor() {}

		void setNormalized(bool normalized);
		void setInterleaved(size_t byteOffset, size_t byteStride);

		GLTFBufferView* bufferView() const { return _pBufferView; }
		GLTFAccessorType type() const { return _type; }
		size_t elementCount() const { return _count; }
		size_t byteOffset() const { return _byteOffset; }
		size_t byteStride() const { return _byteStride; }

		virtual json toJSON() const;

	protected:
		char* _allocate(GLTFBuffer* pBuffer, size_t byteLength);
		void _setData(GLTFBuffer* pBuffer, const char* pData, size_t byteLength);
		const char* _getData() const;

		GLTFBufferView* _pBufferView;
		GLTFAccessorType _type;
		bool _normalized;
		size_t _count;
		size_t _byteOffset;
		size_t _byteStride;
	};
}
 
#endif // _FLOWLIBS_GLTF_ACCESSOR_H
