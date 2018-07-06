/**
* glTF Toolbox CLI
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "gltf/gltf.h"

#include <iostream>

using namespace flow;

int main(int argc, char** ppArgv)
{
	GLTFObject asset;
	asset.setGenerator("https://github.com/framelab/flow-libs");
	asset.setCopyright("(c) 2018 Frame Factory GmbH");

	auto pBuffer = asset.createBuffer();
	auto pPositionAccessor = asset.createAccessor<float>(GLTFAccessorType::VEC3);

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