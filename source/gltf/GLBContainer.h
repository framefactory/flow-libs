/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_GLBCONTAINER_H
#define _FLOWLIBS_GLTF_GLBCONTAINER_H

#include "library.h"
#include <string>


namespace flow
{
	class GLTFObject;

	class GLBContainer
	{
	protected:
		GLBContainer(const GLTFObject* pObject);
		virtual ~GLBContainer() {};

	public:
		bool save(const std::string& fileName) const;

	private:
		const GLTFObject* _pObject;
	};
}

#endif // _FLOWLIBS_GLTF_GLBCONTAINER_H
