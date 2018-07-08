/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_EXTENSION_H
#define _FLOWLIBS_GLTF_EXTENSION_H

#include "library.h"

#include "../core/json.h"
#include <string>


namespace flow
{
	class GLTFElement;

	class F_GLTF_EXPORT GLTFExtension
	{
	public:
		GLTFExtension();
		virtual ~GLTFExtension() {}

		virtual const char* name() const = 0;
		virtual json toJSON() const = 0;

	protected:
	};
}

#endif // _FLOWLIBS_GLTF_EXTENSION_H
