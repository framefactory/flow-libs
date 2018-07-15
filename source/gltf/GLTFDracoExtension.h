/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_DRACOEXTENSION_H
#define _FLOWLIBS_GLTF_DRACOEXTENSION_H

#include "library.h"
#include "GLTFExtension.h"
#include "GLTFConstants.h"

#include "../core/json.h"
#include <string>

namespace flow
{
	class GLTFBufferView;

	class F_GLTF_EXPORT GLTFDracoExtension : public GLTFExtension
	{
	public:
		struct attribute_t
		{
			GLTFAttributeType type;
			int index;
		};

		typedef std::vector<attribute_t> attributeVec_t;

		GLTFDracoExtension();
		virtual ~GLTFDracoExtension() { }

		void setEncodedBufferView(const GLTFBufferView* pBufferView);
		void addAttribute(GLTFAttributeType type, int dracoAttributeIndex);

		const GLTFBufferView* bufferView() const { return _pBufferView; }
		const attributeVec_t attributes() const { return _attributes; }

		virtual const char* name() const;
		virtual json toJSON() const;

	private:
		const GLTFBufferView* _pBufferView;
		attributeVec_t _attributes;
	};
}

#endif // _FLOWLIBS_GLTF_DRACOEXTENSION_H
