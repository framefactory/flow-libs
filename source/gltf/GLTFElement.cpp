/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFElement.h"

using namespace flow;


GLTFElement::GLTFElement(size_t index) :
	_index(index)
{
}

GLTFElement::~GLTFElement()
{
}

std::string GLTFElement::toString(int indent /* = -1 */) const
{
	return toJSON().dump(indent);
}
