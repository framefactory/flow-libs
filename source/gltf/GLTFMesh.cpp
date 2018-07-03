/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFMesh.h"

using namespace flow;
using std::string;


GLTFMesh::GLTFMesh(size_t index, const string& name /* = string{} */) :
	GLTFMainElement(index, name)
{
}

void GLTFMesh::addPrimitive(const GLTFPrimitive& primitive)
{
	_primitives.push_back(primitive);
}

GLTFPrimitive& GLTFMesh::createPrimitive(GLTFPrimitiveMode mode, const GLTFMaterial* pMaterial /* = nullptr */)
{
	_primitives.push_back(GLTFPrimitive(mode, pMaterial));
	return _primitives.back();
}

void GLTFMesh::addWeight(float weight)
{
	_weights.push_back(weight);
}

json GLTFMesh::toJSON() const
{
	json primArr = json::array();
	for (auto it = _primitives.begin(); it != _primitives.end(); ++it) {
		primArr.push_back(it->toJSON());
	}

	json result = GLTFMainElement::toJSON();

	result["primitives"] = primArr;

	if (!_weights.empty()) {
		result["weights"] = _weights;
	}

	return result;
}
