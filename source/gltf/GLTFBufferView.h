/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_BUFFERVIEW_H
#define _FLOWLIBS_GLTF_BUFFERVIEW_H

#include "GLTFElement.h"
#include <string>


namespace flow
{
	enum class GLTFBufferTarget
	{
		UNDEFINED = 0x0000,
		ARRAY_BUFFER = 0x8892,
		ELEMENT_ARRAY_BUFFER = 0x8893
	};

	class GLTFBuffer;

	class GLTFBufferView : public GLTFElement
	{
		friend class GLTFAsset;
		friend class GLTFAccessor;

	protected:
		GLTFBufferView(size_t index, const std::string& name = std::string{});
		virtual ~GLTFBufferView() { }

	public:
		void setBuffer(const GLTFBuffer* pBuffer);
		void setView(size_t byteOffset, size_t byteLength, size_t byteStride = 0);
		void setTarget(GLTFBufferTarget target);

		const GLTFBuffer* buffer() const { return _pBuffer; }
		size_t byteOffset() const { return _byteOffset; }
		size_t byteLength() const { return _byteLength; }
		GLTFBufferTarget target() const { return _target; }

		virtual json toJSON() const;

	private:
		const GLTFBuffer* _pBuffer;
		size_t _byteOffset;
		size_t _byteLength;
		size_t _byteStride;
		GLTFBufferTarget _target;
	};
}

#endif // _FLOWLIBS_GLTF_BUFFERVIEW_H
