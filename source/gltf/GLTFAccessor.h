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
		void addData(GLTFBuffer* pBuffer, const char* pData, size_t byteLength, GLTFBufferViewTarget target);
		char* allocateData(GLTFBuffer* pBuffer, size_t byteLength, GLTFBufferViewTarget target);

		const char* data() const;

		GLTFBufferView* bufferView() const { return _pBufferView; }
		GLTFAccessorType type() const { return _type; }
		virtual GLTFAccessorComponent component() const = 0;
		size_t elementCount() const { return _count; }
		size_t elementByteSize() const { return component().byteSize() * _type.componentCount(); }
		size_t byteOffset() const { return _byteOffset; }
		size_t byteStride() const { return _byteStride; }
		bool normalized() const { return _normalized; }

		virtual json toJSON() const;

	protected:

		GLTFBufferView* _pBufferView;
		GLTFAccessorType _type;
		bool _normalized;
		size_t _count;
		size_t _byteOffset;
		size_t _byteStride;
	};
}
 
#endif // _FLOWLIBS_GLTF_ACCESSOR_H
