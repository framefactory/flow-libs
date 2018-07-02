/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFAccessor.h"
#include "GLTFMaterial.h"
#include "GLTFMesh.h"

using namespace flow;
using std::string;
using std::vector;


GLTFPrimitive::GLTFPrimitive(size_t index) :
	GLTFElement(index, std::string{}),
	_mode(GLTFPrimitiveMode::TRIANGLES),
	_pMaterial(nullptr),
	_pIndicesAccessor(nullptr)
{
}

void GLTFPrimitive::setMode(GLTFPrimitiveMode mode)
{
	_mode = mode;
}

void GLTFPrimitive::setMaterial(const GLTFMaterial* pMaterial)
{
	_pMaterial = pMaterial;
}

void GLTFPrimitive::setIndices(const GLTFAccessor* pAccessor)
{
	_pIndicesAccessor = pAccessor;
}

void GLTFPrimitive::addAttribute(GLTFAttributeType type, const GLTFAccessor* pAccessor)
{
	_attributes.push_back({ type, pAccessor });
}

void GLTFPrimitive::addTargetAttribute(size_t index, GLTFAttributeType type, const GLTFAccessor* pAccessor)
{
	if (index >= _targets.size()) {
		_targets.resize(index + 1);
	}

	_targets[index].push_back({ type, pAccessor });
}

void GLTFPrimitive::addPositions(const GLTFAccessor* pAccessor)
{
	_attributes.push_back({ GLTFAttributeType::POSITION, pAccessor });
}

void GLTFPrimitive::addNormals(const GLTFAccessor* pAccessor)
{
	_attributes.push_back({ GLTFAttributeType::NORMAL, pAccessor });
}

void GLTFPrimitive::addTexCoords(const GLTFAccessor* pAccessor)
{
	_attributes.push_back({ GLTFAttributeType::TEXCOORD_0, pAccessor });
}

json GLTFPrimitive::toJSON() const
{
	json attribDict;
	for (auto it = _attributes.begin(); it != _attributes.end(); ++it) {
		attribDict[_attribName(it->type)] = it->pAccessor->index();
	}

	json result = GLTFElement::toJSON();

	result["attributes"] = attribDict;
	result["mode"] = (int)_mode;

	if (_pIndicesAccessor) {
		result["indices"] = _pIndicesAccessor->index();
	}
	if (_pMaterial) {
		result["material"] = _pMaterial->index();
	}

	if (!_targets.empty()) {
		auto targetArr = json::array();
		for (auto tar_it = _targets.begin(); tar_it != _targets.end(); ++tar_it) {
			auto targetDict = json();
			for (auto atr_it = tar_it->begin(); atr_it != tar_it->end(); ++atr_it) {
				targetDict[_attribName(atr_it->type)] = atr_it->pAccessor->index();
			}
			targetArr.push_back(targetDict);
		}

		result["targets"] = targetArr;
	}

	return result;
}

const char* GLTFPrimitive::_attribName(GLTFAttributeType type) const
{
	switch (type) {
	case GLTFAttributeType::POSITION: return "POSITION";
	case GLTFAttributeType::NORMAL: return "NORMAL";
	case GLTFAttributeType::TANGENT: return "TANGENT";
	case GLTFAttributeType::TEXCOORD_0: return "TEXCOORD_0";
	case GLTFAttributeType::TEXCOORD_1: return "TEXCOORD_1";
	case GLTFAttributeType::COLOR_0: return "COLOR_0";
	case GLTFAttributeType::JOINTS_0: return "JOINTS_0";
	case GLTFAttributeType::WEIGHTS_0: return "WEIGHTS_0";
	default: return "POSITION";
	}
}


GLTFMesh::GLTFMesh(size_t index, const string& name /* = string{} */) :
	GLTFElement(index, name)
{
}

GLTFMesh::~GLTFMesh()
{
	for (auto it = _primitives.begin(); it != _primitives.end(); ++it) {
		delete *it;
	}
}

GLTFPrimitive* GLTFMesh::createPrimitive(GLTFPrimitiveMode mode, const GLTFMaterial* pMaterial /* = nullptr */)
{
	GLTFPrimitive* pPrimitive = new GLTFPrimitive(_primitives.size());
	pPrimitive->setMode(mode);
	pPrimitive->setMaterial(pMaterial);
	_primitives.push_back(pPrimitive);
	return pPrimitive;
}

void GLTFMesh::addWeight(float weight)
{
	_weights.push_back(weight);
}

json GLTFMesh::toJSON() const
{
	json primArr = json::array();
	for (auto it = _primitives.begin(); it != _primitives.end(); ++it) {
		primArr.push_back((*it)->toJSON());
	}

	json result = GLTFElement::toJSON();

	result["primitives"] = primArr;

	if (!_weights.empty()) {
		result["weights"] = _weights;
	}

	return result;
}
