/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFAsset.h"

#include "GLTFScene.h"
#include "GLTFNode.h"
#include "GLTFMesh.h"
#include "GLTFSkin.h"
#include "GLTFCamera.h"
#include "GLTFBuffer.h"
#include "GLTFBufferView.h"
#include "GLTFAccessorT.h"
#include "GLTFMaterial.h"
#include "GLTFTexture.h"
#include "GLTFImage.h"
#include "GLTFSampler.h"
#include "GLTFAnimation.h"

#include "GLTFConstants.h"
#include "GLBContainer.h"

#include "../core/Bit.h"

#include <fstream>

using namespace flow;
using std::string;
using std::vector;
using std::exception;
using std::ofstream;
using std::ios;


GLTFAsset::GLTFAsset() :
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
	_deleteVectorOfPointers(_animations);
}

bool GLTFAsset::saveGLTF(const std::string& gltfFilePath, int indent /*= -1 */)
{
	std::ofstream stream(gltfFilePath, ios::out);
	if (!stream.is_open()) {
		return false;
	}

	stream << toJSON().dump(indent);
	stream.close();

	return true;
}

bool GLTFAsset::saveGLB(const std::string& glbFilePath)
{
	GLBContainer glb(this);
	return glb.save(glbFilePath);
}

void GLTFAsset::setMainScene(const GLTFScene* pScene)
{
	_pMainScene = pScene;
}

void GLTFAsset::setVersion(GLTFVersion version, GLTFVersion minVersion /* = GLTFVersion::UNDEFINED */)
{
	_asset.setVersion(version);
	_asset.setMinVersion(minVersion);
}

void GLTFAsset::setGenerator(const string& generator)
{
	_asset.setGenerator(generator);
}

void GLTFAsset::setCopyright(const string& copyright)
{
	_asset.setCopyright(copyright);
}

void GLTFAsset::addExtension(const GLTFExtension& extension, bool isRequired)
{
	_extensionsUsed.emplace_back(extension.name());
	if (isRequired) {
		_extensionsRequired.emplace_back(extension.name());
	}
}

GLTFScene* GLTFAsset::createScene(const string& name /* = string{} */)
{
	auto pScene = new GLTFScene(_scenes.size(), name);
	_scenes.push_back(pScene);
	return pScene;
}

GLTFNode* GLTFAsset::createNode(const string& name /* = string{} */)
{
	auto pNode = new GLTFNode(_nodes.size(), name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFMeshNode* GLTFAsset::createMeshNode(const GLTFMesh* pMesh, const string& name /* = string{} */)
{
	auto pNode = new GLTFMeshNode(_nodes.size(), pMesh, name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFSkinNode* GLTFAsset::createSkinNode(const GLTFSkin* pSkin, const string& name /* = string{} */)
{
	auto pNode = new GLTFSkinNode(_nodes.size(), pSkin, name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFCameraNode* GLTFAsset::createCameraNode(const GLTFCamera* pCamera, const string& name /* = string{} */)
{
	auto pNode = new GLTFCameraNode(_nodes.size(), pCamera, name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFMesh* GLTFAsset::createMesh(const string& name /* = string{} */)
{
	auto pMesh = new GLTFMesh(_meshes.size(), name);
	_meshes.push_back(pMesh);
	return pMesh;
}

GLTFSkin* GLTFAsset::createSkin(const string& name /* = string{} */)
{
	auto pSkin = new GLTFSkin(_skins.size(), name);
	_skins.push_back(pSkin);
	return pSkin;
}

GLTFCamera* GLTFAsset::createCamera(const string& name /* = string{} */)
{
	auto pCamera = new GLTFCamera(_cameras.size(), name);
	_cameras.push_back(pCamera);
	return pCamera;
}

GLTFBuffer* GLTFAsset::createBuffer(const string& name /* = string{} */)
{
	auto pBuffer = new GLTFBuffer(this, _buffers.size(), name);
	_buffers.push_back(pBuffer);
	return pBuffer;
}

GLTFMaterial* GLTFAsset::createMaterial(const string& name /* = string{} */)
{
	auto pMaterial = new GLTFMaterial(_materials.size());
	_materials.push_back(pMaterial);
	return pMaterial;
}

GLTFTexture* GLTFAsset::createTexture(const GLTFImage* pImage, const GLTFSampler* pSampler /* = nullptr */)
{
	auto pTexture = new GLTFTexture(_textures.size());
	pTexture->setSource(pImage, pSampler);
	_textures.push_back(pTexture);
	return pTexture;
}

GLTFTexture* GLTFAsset::createTexture(const std::string& imageUri, const GLTFSampler* pSampler /* = nullptr */)
{
	auto pImage = new GLTFImage(_images.size());
	pImage->setUri(imageUri);
	_images.push_back(pImage);

	auto pTexture = new GLTFTexture(_textures.size());
	pTexture->setSource(pImage, pSampler);
	_textures.push_back(pTexture);

	return pTexture;
}

GLTFTexture* GLTFAsset::createTexture(GLTFBuffer* pBuffer, const string& imageFilePath, const GLTFSampler* pSampler /* = nullptr */)
{
	auto pBufferView = pBuffer->addImage(imageFilePath);

	if (!pBufferView) {
		return nullptr;
	}

	pBufferView->setTarget(GLTFBufferViewTarget::UNDEFINED);

	size_t dot = imageFilePath.find_last_of('.');
	string ext = imageFilePath.substr(dot + 1);

	auto mimeType = (ext == "png" || ext == "PNG")
		? GLTFMimeType::IMAGE_PNG : GLTFMimeType::IMAGE_JPEG;

	auto pImage = new GLTFImage(_images.size());
	pImage->setBufferView(pBufferView, mimeType);
	_images.push_back(pImage);

	auto pTexture = new GLTFTexture(_textures.size());
	pTexture->setSource(pImage, pSampler);
	_textures.push_back(pTexture);

	return pTexture;

}

GLTFTexture* GLTFAsset::createTexture(const GLTFBufferView* pBufferView, GLTFMimeType mimeType, const GLTFSampler* pSampler /* = nullptr */)
{
	auto pImage = new GLTFImage(_images.size());
	pImage->setBufferView(pBufferView, mimeType);
	_images.push_back(pImage);

	auto pTexture = new GLTFTexture(_textures.size());
	pTexture->setSource(pImage, pSampler);
	_textures.push_back(pTexture);

	return pTexture;
}

GLTFImage* GLTFAsset::createImage(const std::string& imageUri)
{
	auto pImage = new GLTFImage(_images.size());
	pImage->setUri(imageUri);
	_images.push_back(pImage);
	return pImage;
}

GLTFImage* GLTFAsset::createImage(const GLTFBufferView* pBufferView, GLTFMimeType mimeType)
{
	auto pImage = new GLTFImage(_images.size());
	pImage->setBufferView(pBufferView, mimeType);
	_images.push_back(pImage);
	return pImage;
}

GLTFSampler* GLTFAsset::createSampler()
{
	auto pSampler = new GLTFSampler(_samplers.size());
	_samplers.push_back(pSampler);
	return pSampler;
}

GLTFAnimation* GLTFAsset::createAnimation()
{
	// TODO: Implement
	throw exception("not implemented yet");
}

json GLTFAsset::toJSON() const
{
	json result = GLTFElement::toJSON();

	result["asset"] = _asset.toJSON();

	if (_pMainScene) {
		result["scene"] = _pMainScene->index();
	}

	if (!_extensionsUsed.empty()) {
		result["extensionsUsed"] = _extensionsUsed;
	}
	if (!_extensionsRequired.empty()) {
		result["extensionsRequired"] = _extensionsRequired;
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
	_insertElements(result, "animations", _animations);
	
	return result;
}

std::string GLTFAsset::toString(int indent /* = -1 */) const
{
	return toJSON().dump(indent);
}

GLTFBufferView* GLTFAsset::_createBufferView(const string& name /* = string{} */)
{
	auto pBufferView = new GLTFBufferView(_bufferViews.size(), name);
	_bufferViews.push_back(pBufferView);
	return pBufferView;
}

template<typename T>
void GLTFAsset::_insertElements(json& jsonObj, const string& propName, const vector<T*>& vector) const
{
	if (vector.empty()) {
		return;
	}

	auto arr = json::array();
	for (auto it = vector.begin(); it != vector.end(); ++it) {
		arr.emplace_back((*it)->toJSON());
	}

	jsonObj[propName] = arr;
}

template<typename T>
void GLTFAsset::_deleteVectorOfPointers(vector<T*>& vector)
{
	for (auto it = vector.begin(); it != vector.end(); ++it) {
		delete *it;
	}
}

