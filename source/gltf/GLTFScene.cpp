/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFNode.h"
#include "GLTFScene.h"

using namespace flow;
using std::string;


GLTFScene::GLTFScene(size_t index, const string& name /* = string{} */) :
	GLTFElement(index, name)
{
}

GLTFScene::~GLTFScene()
{
}

void GLTFScene::addNode(const GLTFNode* pNode)
{
	_nodes.push_back(pNode);
}

json GLTFScene::toJSON() const
{
	json result = GLTFElement::toJSON();

	if (!_nodes.empty()) {
		auto nodeArray = json::array();
		for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
			nodeArray.push_back((*it)->index());
		}
		result["nodes"] = nodeArray;
	}

	return result;
}
