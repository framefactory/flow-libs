/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLBContainer.h"
#include "GLTFObject.h"

using namespace flow;
using std::string;


GLBContainer::GLBContainer(const GLTFObject* pObject) :
	_pObject(pObject)
{
}

bool GLBContainer::save(const string& fileName) const
{
	return false;
}