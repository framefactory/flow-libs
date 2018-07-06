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
	class F_GLTF_EXPORT GLTFElement
	{
	public:
		GLTFElement() {}
		virtual ~GLTFElement() {}

		void addExtension(std::string& prop, const json& jsonData);
		void setExtras(const json& jsonData);

		const json extensions() const { return _extensions; }
		const json extras() const { return _extras; }

		virtual json toJSON() const;
		virtual std::string toString(int indent = -1) const;

	protected:
		json _extensions;
		json _extras;
	};
}

#endif // _FLOWLIBS_GLTF_ELEMENT_H
