/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_BUFFERVIEW_H
#define _FLOWLIBS_GLTF_BUFFERVIEW_H

#include "library.h"
#include "GLTFMainElement.h"
#include "GLTFConstants.h"

#include <string>


namespace flow
{
	class GLTFBuffer;

	class F_GLTF_EXPORT GLTFBufferView : public GLTFMainElement
	{
		friend class GLTFAsset;
		friend class GLTFBuffer;

	protected:
		GLTFBufferView(size_t index, const std::string& name = std::string{});
		virtual ~GLTFBufferView() { }

	public:
		void setTarget(GLTFBufferViewTarget target);

		char* data() const;
		const GLTFBuffer* buffer() const { return _pBuffer; }
		size_t byteOffset() const { return _byteOffset; }
		size_t byteLength() const { return _byteLength; }
		GLTFBufferViewTarget target() const { return _target; }

		virtual json toJSON() const;

	private:
		void _set(GLTFBuffer* pBuffer, size_t byteOffset, size_t byteLength, size_t byteStride = 0);

		GLTFBuffer* _pBuffer;
		size_t _byteOffset;
		size_t _byteLength;
		size_t _byteStride;
		GLTFBufferViewTarget _target;
	};
}

#endif // _FLOWLIBS_GLTF_BUFFERVIEW_H
