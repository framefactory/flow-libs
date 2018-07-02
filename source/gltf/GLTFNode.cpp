/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFMesh.h"
#include "GLTFCamera.h"
#include "GLTFSkin.h"
#include "GLTFNode.h"

using namespace flow;
using std::string;


GLTFNode::GLTFNode(size_t index, const string& name /* = string{} */) :
	GLTFElement(index, name),
	_pMatrix(nullptr),
	_pTranslation(nullptr),
	_pRotation(nullptr),
	_pScale(nullptr)
{
}

GLTFNode::~GLTFNode()
{
	F_SAFE_DELETE(_pMatrix);
	F_SAFE_DELETE(_pTranslation);
	F_SAFE_DELETE(_pRotation);
	F_SAFE_DELETE(_pScale);
}

void GLTFNode::addChild(const GLTFNode* pNode)
{
	_children.push_back(pNode);
}

void GLTFNode::setMatrix(const Matrix4f& matrix)
{
	F_SAFE_DELETE(_pMatrix);
	F_SAFE_DELETE(_pTranslation);
	F_SAFE_DELETE(_pRotation);
	F_SAFE_DELETE(_pScale);

	_pMatrix = new Matrix4f(matrix);
}

void GLTFNode::setTranslation(const Vector3f& translation)
{
	F_SAFE_DELETE(_pMatrix);
	F_SAFE_DELETE(_pTranslation);

	_pTranslation = new Vector3f(translation);
}

void GLTFNode::setRotation(const Quaternion4f& rotation)
{
	F_SAFE_DELETE(_pMatrix);
	F_SAFE_DELETE(_pRotation);

	_pRotation = new Quaternion4f(rotation);
}

void GLTFNode::setScale(const Vector3f& scale)
{
	F_SAFE_DELETE(_pMatrix);
	F_SAFE_DELETE(_pScale);

	_pScale = new Vector3f(scale);
}

void GLTFNode::setTRS(const Vector3f& translation, const Quaternion4f& rotation, const Vector3f& scale)
{
	F_SAFE_DELETE(_pMatrix);
	F_SAFE_DELETE(_pTranslation);
	F_SAFE_DELETE(_pRotation);
	F_SAFE_DELETE(_pScale);

	_pTranslation = new Vector3f(translation);
	_pRotation = new Quaternion4f(rotation);
	_pScale = new Vector3f(scale);
}

json GLTFNode::toJSON() const
{
	json result = GLTFElement::toJSON();
	
	if (!_children.empty()) {
		auto nodeArray = json::array();
		for (auto it = _children.begin(); it != _children.end(); ++it) {
			nodeArray.push_back((*it)->index());
		}

		result["children"] = nodeArray;
	}

	if (_pMatrix) {
		result["matrix"] = _pMatrix->toJSON();
	}
	else {
		if (_pTranslation) {
			result["translation"] = _pTranslation->toJSON();
		}
		if (_pRotation) {
			result["rotation"] = _pRotation->toJSON();
		}
		if (_pScale) {
			result["scale"] = _pScale->toJSON();
		}
	}

	return result;
}

GLTFMeshNode::GLTFMeshNode(size_t index, const GLTFMesh* pMesh, const string& name /* = string{} */) :
	GLTFNode(index, name),
	_pMesh(pMesh)
{
}

json GLTFMeshNode::toJSON() const
{
	json result = GLTFNode::toJSON();
	result["mesh"] = _pMesh->index();
	return result;
}

GLTFCameraNode::GLTFCameraNode(size_t index, const GLTFCamera* pCamera, const string& name /* = string{} */) :
	GLTFNode(index, name),
	_pCamera(pCamera)
{
}

json GLTFCameraNode::toJSON() const
{
	json result = GLTFNode::toJSON();
	result["camera"] = _pCamera->index();
	return result;
}

GLTFSkinNode::GLTFSkinNode(size_t index, const GLTFSkin* pSkin, const string& name /* = string{} */) :
	GLTFNode(index, name),
	_pSkin(pSkin)
{
}

json GLTFSkinNode::toJSON() const
{
	json result = GLTFNode::toJSON();
	result["skin"] = _pSkin->index();
	return result;
}
