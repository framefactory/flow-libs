/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFNode.h"
#include "GLTFScene.h"

using namespace flow;


GLTFScene::GLTFScene(size_t index, const std::string& name /* = "" */) :
	GLTFElement(index),
	_name(name)
{
}

GLTFScene::~GLTFScene()
{
}

void GLTFScene::setName(const std::string& name)
{
	_name = name;
}

void GLTFScene::addNode(const GLTFNode* pNode)
{
	_nodes.push_back(pNode);
}

json GLTFScene::toJSON() const
{
	auto nodeArray = json::array();
	for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
		nodeArray.push_back((*it)->index());
	}

	return json({
		{ "name", _name },
		{ "nodes", nodeArray }
	});
}
