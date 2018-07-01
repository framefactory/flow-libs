/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_ELEMENT_H
#define _FLOWLIBS_GLTF_ELEMENT_H

#include "../core/json.h"


namespace flow
{
	class GLTFElement
	{
	public:
		GLTFElement(size_t index);
		virtual ~GLTFElement();

		virtual json toJSON() const = 0;
		virtual std::string toString(int indent = -1) const;

		size_t index() const { return _index;  }

	protected:
		size_t _index;
	};
}

#endif // _FLOWLIBS_GLTF_ELEMENT_H
