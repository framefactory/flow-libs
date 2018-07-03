/**
* glTF Toolbox CLI
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "gltf/GLTFObject.h"
#include "gltf/GLTFScene.h"
#include "gltf/GLTFNode.h"
#include "gltf/GLTFMesh.h"
#include "gltf/GLTFAccessor.h"

#include <iostream>

using namespace flow;

int main(int argc, char** ppArgv)
{
	GLTFObject asset;
	asset.setGenerator("https://github.com/framelab/flow-libs");
	asset.setCopyright("(c) 2018 Frame Factory GmbH");

	auto pBuffer = asset.createBuffer(65536);
	auto pBufferView = asset.createBufferView(pBuffer);
	auto pPositionAccessor = asset.createAccessor(pBufferView);
	pPositionAccessor->setType(GLTFAccessorType::VEC3, GLTFAccessorComponent::FLOAT);

	auto pMesh = asset.createMesh();
	auto& primitive = pMesh->createPrimitive(GLTFPrimitiveMode::TRIANGLES);
	primitive.addPositions(pPositionAccessor);

	auto pMeshNode = asset.createMeshNode(pMesh, "My Mesh");
	pMeshNode->setTranslation({ 1.0f, 2.0f, 3.0f });

	auto pScene = asset.createScene("My Scene");
	asset.setMainScene(pScene);
	pScene->addNode(pMeshNode);

	std::cout << asset.toString(2);
}