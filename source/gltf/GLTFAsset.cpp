/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFElement.h"
#include "GLTFScene.h"
#include "GLTFNode.h"
#include "GLTFMesh.h"
#include "GLTFSkin.h"
#include "GLTFCamera.h"
#include "GLTFBuffer.h"
#include "GLTFBufferView.h"
#include "GLTFAccessor.h"
#include "GLTFMaterial.h"
#include "GLTFTexture.h"
#include "GLTFImage.h"
#include "GLTFSampler.h"
//#include "GLTFAnimation.h"

#include "GLTFAsset.h"

using namespace flow;


GLTFAsset::GLTFAsset() :
	_version(Version::GLTF_2_0),
	_pMainScene(nullptr)
{
}

GLTFAsset::~GLTFAsset()
{
	_deleteVectorOfPointers(_scenes);
	_deleteVectorOfPointers(_nodes);
	_deleteVectorOfPointers(_meshes);
	_deleteVectorOfPointers(_skins);
	_deleteVectorOfPointers(_cameras);
	_deleteVectorOfPointers(_buffers);
	_deleteVectorOfPointers(_bufferViews);
	_deleteVectorOfPointers(_accessors);
	_deleteVectorOfPointers(_materials);
	_deleteVectorOfPointers(_textures);
	_deleteVectorOfPointers(_images);
	_deleteVectorOfPointers(_samplers);
	//_deleteVectorOfPointers(_animations);
}

void GLTFAsset::setMainScene(const GLTFScene* pScene)
{
	_pMainScene = pScene;
}

void GLTFAsset::setVersion(Version version)
{
	_version = version;
}

void GLTFAsset::setGenerator(const std::string& generator)
{
	_generator = generator;
}

void GLTFAsset::setCopyright(const std::string& copyright)
{
	_copyright = copyright;
}

GLTFScene* GLTFAsset::createScene(const std::string& name /* = "" */)
{
	auto pScene = new GLTFScene(_scenes.size(), name);
	_scenes.push_back(pScene);
	return pScene;
}

GLTFNode* GLTFAsset::createNode(const std::string& name /* = "" */)
{
	auto pNode = new GLTFNode(_nodes.size(), name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFMeshNode* GLTFAsset::createMeshNode(const GLTFMesh* pMesh, const std::string& name /* = "" */)
{
	auto pNode = new GLTFMeshNode(_nodes.size(), pMesh, name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFSkinNode* GLTFAsset::createSkinNode(const GLTFSkin* pSkin, const std::string& name /* = "" */)
{
	auto pNode = new GLTFSkinNode(_nodes.size(), pSkin, name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFCameraNode* GLTFAsset::createCameraNode(const GLTFCamera* pCamera, const std::string& name /* = "" */)
{
	auto pNode = new GLTFCameraNode(_nodes.size(), pCamera, name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFCamera* GLTFAsset::createCamera()
{
	auto pCamera = new GLTFCamera(_cameras.size());
	_cameras.push_back(pCamera);
	return pCamera;
}

GLTFMesh* GLTFAsset::createMesh()
{
	auto pMesh = new GLTFMesh(_meshes.size());
	_meshes.push_back(pMesh);
	return pMesh;
}

GLTFBuffer* GLTFAsset::createBuffer(size_t byteLength)
{
	auto pBuffer = new GLTFBuffer(_buffers.size(), byteLength);
	_buffers.push_back(pBuffer);
	return pBuffer;
}

GLTFBufferView* GLTFAsset::createBufferView(const GLTFBuffer* pBuffer)
{
	auto pBufferView = new GLTFBufferView(_bufferViews.size(), pBuffer);
	_bufferViews.push_back(pBufferView);
	return pBufferView;
}

GLTFAccessor* GLTFAsset::createAccessor(const GLTFBufferView* pView)
{
	auto pAccessor = new GLTFAccessor(_accessors.size(), pView);
	_accessors.push_back(pAccessor);
	return pAccessor;
}

GLTFMaterial* GLTFAsset::createMaterial()
{
	auto pMaterial = new GLTFMaterial(_materials.size());
	_materials.push_back(pMaterial);
	return pMaterial;
}

GLTFTexture* GLTFAsset::createTexture()
{
	auto pTexture = new GLTFTexture(_textures.size());
	_textures.push_back(pTexture);
	return pTexture;
}

GLTFImage* GLTFAsset::createImage()
{
	auto pImage = new GLTFImage(_images.size());
	_images.push_back(pImage);
	return pImage;
}

GLTFSampler* GLTFAsset::createSampler()
{
	auto pSampler = new GLTFSampler(_samplers.size());
	_samplers.push_back(pSampler);
	return pSampler;
}

GLTFSkin* GLTFAsset::createSkin()
{
	// TODO: Implement
	throw std::exception("not implemented yet");
}

GLTFAnimation* GLTFAsset::createAnimation()
{
	// TODO: Implement
	throw std::exception("not implemented yet");
}

json GLTFAsset::toJSON() const
{
	auto asset = json({
		{ "version", _versionToString() }
	});

	if (!_generator.empty()) {
		asset["generator"] = _generator;
	}

	if (!_copyright.empty()) {
		asset["copyright"] = _copyright;
	}

	auto result = json({
		{ "asset", asset },
	});

	if (_pMainScene) {
		result["scene"] = _pMainScene->index();
	}

	_insertElements(result, "scenes", _scenes);
	_insertElements(result, "nodes", _nodes);
	_insertElements(result, "meshes", _meshes);
	_insertElements(result, "skins", _skins);
	_insertElements(result, "cameras", _cameras);
	_insertElements(result, "buffers", _buffers);
	_insertElements(result, "bufferViews", _bufferViews);
	_insertElements(result, "accessors", _accessors);
	_insertElements(result, "materials", _materials);
	_insertElements(result, "textures", _textures);
	_insertElements(result, "images", _images);
	_insertElements(result, "samplers", _samplers);
	//_insertElements(result, "animations", _animations);

	
	return result;
}

std::string GLTFAsset::toString(int indent /* = -1 */) const
{
	return toJSON().dump(indent);
}

template<typename T>
void GLTFAsset::_insertElements(json& jsonObj, const std::string& propName, const std::vector<T*>& vector) const
{
	if (vector.empty()) {
		return;
	}

	auto arr = json::array();
	for (auto it = vector.begin(); it != vector.end(); ++it) {
		arr.push_back((*it)->toJSON());
	}

	jsonObj[propName] = arr;
}

template<typename T>
void GLTFAsset::_deleteVectorOfPointers(std::vector<T*>& vector)
{
	for (auto it = vector.begin(); it != vector.end(); ++it) {
		delete *it;
	}
}

const char* GLTFAsset::_versionToString() const
{
	switch (_version) {
	case Version::GLTF_1_0: return "1.0";
	case Version::GLTF_2_0: default: return "2.0";
	}
}
