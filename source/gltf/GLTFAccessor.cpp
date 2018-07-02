/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFAccessor.h"
#include "GLTFBufferView.h"

using namespace flow;
using std::string;
using std::vector;


GLTFAccessor::GLTFAccessor(size_t index, const string& name /* = std::string{} */) :
	GLTFElement(index, name),
	_pBufferView(nullptr),
	_type(GLTFAccessorType::SCALAR),
	_componentType(GLTFAccessorComponent::FLOAT),
	_normalized(false),
	_count(0),
	_byteOffset(0),
	_byteStride(0)
{
}

GLTFAccessor::~GLTFAccessor()
{
}

void GLTFAccessor::setBufferView(const GLTFBufferView* pBufferView)
{
	_pBufferView = pBufferView;
}

void GLTFAccessor::setType(GLTFAccessorType type, GLTFAccessorComponent component, bool normalized /* = false */)
{
	_type = type;
	_componentType = component;
	_normalized = normalized;
}

void GLTFAccessor::setRange(size_t elementCount, size_t byteOffset, size_t byteStride /* = 0 */)
{
	_count = elementCount;
	_byteOffset = _byteOffset;
	_byteStride = _byteStride;
}

void GLTFAccessor::setMin(const vector<float>& min)
{
	_min = min;
}

void GLTFAccessor::setMax(const vector<float>& max)
{
	_max = max;
}

json GLTFAccessor::toJSON() const
{
	json result = GLTFElement::toJSON();

	result["type"] = _typeName(_type);
	result["componentType"] = (int)_componentType;
	result["count"] = _count;

	if (_pBufferView) {
		result["bufferView"] = _pBufferView->index();
	}
	if (_byteOffset > 0) {
		result["byteOffset"] = _byteOffset;
	}
	if (_byteStride > 0) {
		result["byteStride"] = _byteStride;
	}
	if (_normalized) {
		result["normalized"] = true;
	}
	if (!_min.empty()) {
		result["min"] = _min;
	}
	if (!_max.empty()) {
		result["max"] = _max;
	}

	return result;
}

const char* GLTFAccessor::_typeName(GLTFAccessorType type) const
{
	switch (type) {
	case GLTFAccessorType::SCALAR: return "SCALAR";
	case GLTFAccessorType::VEC2: return "VEC2";
	case GLTFAccessorType::VEC3: return "VEC3";
	case GLTFAccessorType::VEC4: return "VEC4";
	case GLTFAccessorType::MAT2: return "MAT2";
	case GLTFAccessorType::MAT3: return "MAT3";
	case GLTFAccessorType::MAT4: return "MAT4";
	default: return "SCALAR";
	}
}

const size_t GLTFAccessor::_componentCount(GLTFAccessorType type) const
{
	switch (type) {
	case GLTFAccessorType::SCALAR: return 1;
	case GLTFAccessorType::VEC2: return 2;
	case GLTFAccessorType::VEC3: return 3;
	case GLTFAccessorType::VEC4: return 4;
	case GLTFAccessorType::MAT2: return 4;
	case GLTFAccessorType::MAT3: return 9;
	case GLTFAccessorType::MAT4: return 16;
	default: return 1;
	}
}

const size_t GLTFAccessor::_componentSize(GLTFAccessorComponent component) const
{
	switch (component) {
	case GLTFAccessorComponent::BYTE: return 1;
	case GLTFAccessorComponent::UNSIGNED_BYTE: return 1;
	case GLTFAccessorComponent::SHORT: return 2;
	case GLTFAccessorComponent::UNSIGNED_SHORT: return 2;
	case GLTFAccessorComponent::INT: return 4;
	case GLTFAccessorComponent::UNSIGNED_INT: return 4;
	case GLTFAccessorComponent::FLOAT: return 4;
	default: return 1;
	}
}
