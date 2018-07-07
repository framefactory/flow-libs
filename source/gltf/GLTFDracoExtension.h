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

#include "../core/json.h"
#include <string>


namespace flow
{
	class F_GLTF_EXPORT GLTFDracoExtension : public GLTFExtension
	{
	public:
		GLTFDracoExtension();
		virtual ~GLTFDracoExtension() {}

		virtual const char* name() const;

	protected:
	};
}

#endif // _FLOWLIBS_GLTF_DRACOEXTENSION_H
