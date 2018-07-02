/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_ELEMENT_H
#define _FLOWLIBS_GLTF_ELEMENT_H

#include "library.h"
#include "../core/json.h"

#include <string>


namespace flow
{
	class GLTFElement
	{
	public:
		GLTFElement(size_t index, const std::string& name);
		virtual ~GLTFElement() { }

		virtual json toJSON() const;
		virtual std::string toString(int indent = -1) const;

		void setName(const std::string& name);
		void addExtension(std::string& prop, const json& jsonData);
		void setExtras(const json& jsonData);

		size_t index() const { return _index;  }

	protected:
		size_t _index;
		std::string _name;
		json _extensions;
		json _extras;
	};
}

#endif // _FLOWLIBS_GLTF_ELEMENT_H
