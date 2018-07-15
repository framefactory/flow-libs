/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFDracoExtension.h"
#include "GLTFBufferView.h"

using namespace flow;
using std::string;


GLTFDracoExtension::GLTFDracoExtension() :
	_pBufferView(nullptr)
{
}

void GLTFDracoExtension::setEncodedBufferView(const GLTFBufferView* pBufferView)
{
	_pBufferView = pBufferView;
}

void GLTFDracoExtension::addAttribute(GLTFAttributeType type, int dracoAttributeIndex)
{
	_attributes.push_back({ type, dracoAttributeIndex });
}

const char* GLTFDracoExtension::name() const
{
	return "KHR_draco_mesh_compression";
}

json GLTFDracoExtension::toJSON() const
{
	json result{
		{ "bufferView", _pBufferView->index() }
	};

	if (!_attributes.empty()) {
		json attribDict;
		for (auto it = _attributes.begin(); it != _attributes.end(); ++it) {
			attribDict[it->type.name()] = it->index;
		}
		result["attributes"] = attribDict;
	}

	return result;
}
