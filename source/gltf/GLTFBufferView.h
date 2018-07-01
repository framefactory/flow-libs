/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_BUFFERVIEW_H
#define _FLOWLIBS_GLTF_BUFFERVIEW_H

#include "GLTFElement.h"


namespace flow
{
	class GLTFBuffer;

	class GLTFBufferView : public GLTFElement
	{
		friend class GLTFAsset;
		friend class GLTFAccessor;

	public:
		enum Target {
			UNDEFINED            = 0x0000,
			ARRAY_BUFFER         = 0x8892,
			ELEMENT_ARRAY_BUFFER = 0x8893
		};

	protected:
		GLTFBufferView(size_t index, const GLTFBuffer* pBuffer);
		virtual ~GLTFBufferView() { }

	public:
		void setView(size_t offset, size_t length);
		void setTarget(Target target);

		virtual json toJSON() const;

	private:
		const GLTFBuffer* _pBuffer;
		size_t _byteOffset;
		size_t _byteLength;
		Target _target;
	};
}

#endif // _FLOWLIBS_GLTF_BUFFERVIEW_H
