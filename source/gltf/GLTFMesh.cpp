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


GLTFPrimitive::GLTFPrimitive(size_t index, Mode mode, const GLTFMaterial* pMaterial /* = nullptr */) :
	GLTFElement(index),
	_mode(mode),
	_pMaterial(pMaterial),
	_pIndicesAccessor(nullptr)
{
}

GLTFPrimitive::~GLTFPrimitive()
{
}

void GLTFPrimitive::setMode(Mode mode)
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

void GLTFPrimitive::addAttribute(GLTFAttribute::Type type, const GLTFAccessor* pAccessor)
{
	_attributes.push_back({ type, pAccessor });
}

void GLTFPrimitive::addTargetAttribute(size_t index, GLTFAttribute::Type type, const GLTFAccessor* pAccessor)
{
	if (index >= _targets.size()) {
		_targets.resize(index + 1);
	}

	_targets[index].push_back({ type, pAccessor });
}

void GLTFPrimitive::addPositions(const GLTFAccessor* pAccessor)
{
	_attributes.push_back({ GLTFAttribute::Type::POSITION, pAccessor });
}

void GLTFPrimitive::addNormals(const GLTFAccessor* pAccessor)
{
	_attributes.push_back({ GLTFAttribute::Type::NORMAL, pAccessor });
}

void GLTFPrimitive::addTexCoords(const GLTFAccessor* pAccessor)
{
	_attributes.push_back({ GLTFAttribute::Type::TEXCOORD_0, pAccessor });
}

json GLTFPrimitive::toJSON() const
{
	auto attribDict = json();
	for (auto it = _attributes.begin(); it != _attributes.end(); ++it) {
		attribDict[_attribName(it->type)] = it->pAccessor->index();
	}

	auto result = json({
		{ "attributes", attribDict },
		{ "mode", (size_t)_mode }
	});

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

const char* GLTFPrimitive::_attribName(GLTFAttribute::Type type) const
{
	switch (type) {
	case GLTFAttribute::Type::POSITION: return "POSITION";
	case GLTFAttribute::Type::NORMAL: return "NORMAL";
	case GLTFAttribute::Type::TANGENT: return "TANGENT";
	case GLTFAttribute::Type::TEXCOORD_0: return "TEXCOORD_0";
	case GLTFAttribute::Type::TEXCOORD_1: return "TEXCOORD_1";
	case GLTFAttribute::Type::COLOR_0: return "COLOR_0";
	case GLTFAttribute::Type::JOINTS_0: return "JOINTS_0";
	case GLTFAttribute::Type::WEIGHTS_0: return "WEIGHTS_0";
	default: return "POSITION";
	}
}


GLTFMesh::GLTFMesh(size_t index) :
	GLTFElement(index)
{
}

GLTFMesh::~GLTFMesh()
{
	for (auto it = _primitives.begin(); it != _primitives.end(); ++it) {
		delete *it;
	}
}

GLTFPrimitive* GLTFMesh::createPrimitive(GLTFPrimitive::Mode mode, const GLTFMaterial* pMaterial /* = nullptr */)
{
	GLTFPrimitive* pPrimitive = new GLTFPrimitive(_primitives.size(), mode, pMaterial);
	_primitives.push_back(pPrimitive);
	return pPrimitive;
}

void GLTFMesh::addWeight(float weight)
{
	_weights.push_back(weight);
}

json GLTFMesh::toJSON() const
{
	auto primArr = json::array();
	for (auto it = _primitives.begin(); it != _primitives.end(); ++it) {
		primArr.push_back((*it)->toJSON());
	}

	auto result = json({
		{ "primitives", primArr }
	});

	if (!_weights.empty()) {
		result["weights"] = _weights;
	}

	return result;
}
