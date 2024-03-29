/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFPrimitive.h"
#include "GLTFAccessor.h"
#include "GLTFMaterial.h"

using namespace flow;
using std::string;


GLTFPrimitive::GLTFPrimitive(GLTFPrimitiveMode mode /* = GLTFPrimitiveMode::TRIANGLES */, const GLTFMaterial* pMaterial /* = nullptr */) :
	_mode(mode),
	_pMaterial(pMaterial),
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

const GLTFAccessor* GLTFPrimitive::attributeAccessor(GLTFAttributeType type) const
{
	for (size_t i = 0; i < _attributes.size(); ++i) {
		if (type == _attributes[i].type) {
			return _attributes[i].pAccessor;
		}
	}

	return nullptr;
}

json GLTFPrimitive::toJSON() const
{
	json result = GLTFElement::toJSON();

	result["mode"] = (int)_mode;

	if (!_attributes.empty()) {
		json attribDict;
		for (auto it = _attributes.begin(); it != _attributes.end(); ++it) {
			attribDict[it->type.name()] = it->pAccessor->index();
		}
		result["attributes"] = attribDict;
	}

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
				targetDict[atr_it->type.name()] = atr_it->pAccessor->index();
			}
			targetArr.push_back(targetDict);
		}

		result["targets"] = targetArr;
	}

	return result;
}
