/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFAccessor.h"
#include "GLTFBufferView.h"

using namespace flow;


GLTFAccessor::GLTFAccessor(size_t index, const GLTFBufferView* pView) :
	GLTFElement(index),
	_pBufferView(pView),
	_type(Type::SCALAR),
	_componentType(ComponentType::FLOAT),
	_count(0),
	_byteOffset(0),
	_byteStride(0)
{
}

GLTFAccessor::~GLTFAccessor()
{
}

void GLTFAccessor::setType(Type type, ComponentType componentType)
{
	_type = type;
	_componentType = componentType;
}

void GLTFAccessor::setAccess(size_t elementCount, size_t byteOffset, size_t byteStride /* = 0 */)
{
	_count = elementCount;
	_byteOffset = _byteOffset;
	_byteStride = _byteStride;
}

void GLTFAccessor::setMin(const std::vector<float>& min)
{
	_min = min;
}

void GLTFAccessor::setMax(const std::vector<float>& max)
{
	_max = max;
}

json GLTFAccessor::toJSON() const
{
	auto result = json({
		{ "bufferView", _pBufferView->index() },
		{ "byteOffset", _byteOffset },
		{ "componentType", (size_t)_componentType },
		{ "type", typeName(_type) },
		{ "count", _count }
	});

	if (_byteStride > 0) {
		result["byteStride"] = _byteStride;
	}
	if (!_min.empty()) {
		result["min"] = _min;
	}
	if (!_max.empty()) {
		result["max"] = _max;
	}

	return result;
}

const char* GLTFAccessor::typeName(Type type) const
{
	switch (type) {
	case Type::SCALAR: return "SCALAR";
	case Type::VEC2: return "VEC2";
	case Type::VEC3: return "VEC3";
	case Type::VEC4: return "VEC4";
	case Type::MAT2: return "MAT2";
	case Type::MAT3: return "MAT3";
	case Type::MAT4: return "MAT4";
	default: return "SCALAR";
	}
}

const size_t GLTFAccessor::componentCount(Type type) const
{
	switch (type) {
	case Type::SCALAR: return 1;
	case Type::VEC2: return 2;
	case Type::VEC3: return 3;
	case Type::VEC4: return 4;
	case Type::MAT2: return 4;
	case Type::MAT3: return 9;
	case Type::MAT4: return 16;
	default: return 1;
	}
}

const size_t GLTFAccessor::componentSize(ComponentType componentType) const
{
	switch (componentType) {
	case ComponentType::BYTE: return 1;
	case ComponentType::UNSIGNED_BYTE: return 1;
	case ComponentType::SHORT: return 2;
	case ComponentType::UNSIGNED_SHORT: return 2;
	case ComponentType::INT: return 4;
	case ComponentType::UNSIGNED_INT: return 4;
	case ComponentType::FLOAT: return 4;
	default: return 1;
	}
}

//json GLTFAccessor::vecToArray(const std::vector<float>& vector) const
//{
//}
