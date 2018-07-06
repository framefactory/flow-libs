/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFObject.h"

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

#include <fstream>

using namespace flow;
using std::string;
using std::vector;
using std::exception;
using std::ofstream;
using std::ios;

GLTFObject::GLTFObject() :
	_pMainScene(nullptr)
{
}

GLTFObject::~GLTFObject()
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

bool GLTFObject::save(const std::string& gltfFilePath)
{
	std::ofstream stream(gltfFilePath, ios::out);
	if (!stream.is_open()) {
		return false;
	}

	stream << toJSON().dump(2);
	stream.close();

	return true;
}

void GLTFObject::setMainScene(const GLTFScene* pScene)
{
	_pMainScene = pScene;
}

void GLTFObject::setVersion(GLTFVersion version, GLTFVersion minVersion /* = GLTFVersion::UNDEFINED */)
{
	_asset.setVersion(version);
	_asset.setMinVersion(minVersion);
}

void GLTFObject::setGenerator(const string& generator)
{
	_asset.setGenerator(generator);
}

void GLTFObject::setCopyright(const string& copyright)
{
	_asset.setCopyright(copyright);
}

GLTFScene* GLTFObject::createScene(const string& name /* = string{} */)
{
	auto pScene = new GLTFScene(_scenes.size(), name);
	_scenes.push_back(pScene);
	return pScene;
}

GLTFNode* GLTFObject::createNode(const string& name /* = string{} */)
{
	auto pNode = new GLTFNode(_nodes.size(), name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFMeshNode* GLTFObject::createMeshNode(const GLTFMesh* pMesh, const string& name /* = string{} */)
{
	auto pNode = new GLTFMeshNode(_nodes.size(), pMesh, name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFSkinNode* GLTFObject::createSkinNode(const GLTFSkin* pSkin, const string& name /* = string{} */)
{
	auto pNode = new GLTFSkinNode(_nodes.size(), pSkin, name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFCameraNode* GLTFObject::createCameraNode(const GLTFCamera* pCamera, const string& name /* = string{} */)
{
	auto pNode = new GLTFCameraNode(_nodes.size(), pCamera, name);
	_nodes.push_back(pNode);
	return pNode;
}

GLTFMesh* GLTFObject::createMesh(const string& name /* = string{} */)
{
	auto pMesh = new GLTFMesh(_meshes.size(), name);
	_meshes.push_back(pMesh);
	return pMesh;
}

GLTFSkin* GLTFObject::createSkin(const string& name /* = string{} */)
{
	auto pSkin = new GLTFSkin(_skins.size(), name);
	_skins.push_back(pSkin);
	return pSkin;
}

GLTFCamera* GLTFObject::createCamera(const string& name /* = string{} */)
{
	auto pCamera = new GLTFCamera(_cameras.size(), name);
	_cameras.push_back(pCamera);
	return pCamera;
}

GLTFBuffer* GLTFObject::createBuffer(const string& name /* = string{} */)
{
	auto pBuffer = new GLTFBuffer(this, _buffers.size(), name);
	_buffers.push_back(pBuffer);
	return pBuffer;
}

GLTFMaterial* GLTFObject::createMaterial(const string& name /* = string{} */)
{
	auto pMaterial = new GLTFMaterial(_materials.size());
	_materials.push_back(pMaterial);
	return pMaterial;
}

GLTFTexture* GLTFObject::createTexture(const GLTFImage* pImage, const GLTFSampler* pSampler /* = nullptr */)
{
	auto pTexture = new GLTFTexture(_textures.size());
	pTexture->setSource(pImage, pSampler);
	_textures.push_back(pTexture);
	return pTexture;
}

GLTFTexture* GLTFObject::createTexture(const std::string& imageUri, const GLTFSampler* pSampler /* = nullptr */)
{
	auto pImage = new GLTFImage(_images.size());
	pImage->setUri(imageUri);
	_images.push_back(pImage);

	auto pTexture = new GLTFTexture(_textures.size());
	pTexture->setSource(pImage, pSampler);
	_textures.push_back(pTexture);

	return pTexture;
}

GLTFTexture* GLTFObject::createTexture(const GLTFBufferView* pBufferView, GLTFMimeType mimeType, const GLTFSampler* pSampler /* = nullptr */)
{
	auto pImage = new GLTFImage(_images.size());
	pImage->setBufferView(pBufferView, mimeType);
	_images.push_back(pImage);

	auto pTexture = new GLTFTexture(_textures.size());
	pTexture->setSource(pImage, pSampler);
	_textures.push_back(pTexture);

	return pTexture;
}

GLTFImage* GLTFObject::createImage(const std::string& imageUri)
{
	auto pImage = new GLTFImage(_images.size());
	pImage->setUri(imageUri);
	_images.push_back(pImage);
	return pImage;
}

GLTFImage* GLTFObject::createImage(const GLTFBufferView* pBufferView, GLTFMimeType mimeType)
{
	auto pImage = new GLTFImage(_images.size());
	pImage->setBufferView(pBufferView, mimeType);
	_images.push_back(pImage);
	return pImage;
}

GLTFSampler* GLTFObject::createSampler()
{
	auto pSampler = new GLTFSampler(_samplers.size());
	_samplers.push_back(pSampler);
	return pSampler;
}

GLTFAnimation* GLTFObject::createAnimation()
{
	// TODO: Implement
	throw exception("not implemented yet");
}

json GLTFObject::toJSON() const
{
	json result = GLTFElement::toJSON();

	result["asset"] = _asset.toJSON();

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
	_insertElements(result, "animations", _animations);
	
	return result;
}

std::string GLTFObject::toString(int indent /* = -1 */) const
{
	return toJSON().dump(indent);
}

GLTFBufferView* GLTFObject::_createBufferView(const string& name /* = string{} */)
{
	auto pBufferView = new GLTFBufferView(_bufferViews.size(), name);
	_bufferViews.push_back(pBufferView);
	return pBufferView;
}

template<typename T>
void GLTFObject::_insertElements(json& jsonObj, const string& propName, const vector<T*>& vector) const
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
void GLTFObject::_deleteVectorOfPointers(vector<T*>& vector)
{
	for (auto it = vector.begin(); it != vector.end(); ++it) {
		delete *it;
	}
}

