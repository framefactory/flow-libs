/**
 * Flow Libs - glTF
 *
 * @author Ralph Wiedemeier <ralph@framefactory.io>
 * @copyright (c) 2018 Frame Factory GmbH.
 */

#include "GLTFConstants.h"

using namespace flow;


const char* GLTFVersion::name() const
{
	switch (_state) {
		F_ENUM_CASE(UNDEFINED, "UNDEFINED");
		F_ENUM_CASE(GLTF_1_0, "1.0");
		F_ENUM_CASE(GLTF_2_0, "2.0");
		F_ENUM_ASSERT_DEFAULT;
	}
}

const char* GLTFBufferViewTarget::name() const
{
	switch (_state) {
		F_ENUM_NAME(UNDEFINED);
		F_ENUM_NAME(ARRAY_BUFFER);
		F_ENUM_NAME(ELEMENT_ARRAY_BUFFER);
		F_ENUM_ASSERT_DEFAULT;
	}
}

size_t GLTFAccessorType::componentCount() const
{
	switch (_state) {
	case SCALAR: return 1;
	case VEC2: return 2;
	case VEC3: return 3;
	case VEC4: return 4;
	case MAT2: return 4;
	case MAT3: return 9;
	case MAT4: return 16;
	default: F_ASSERT(false); return 1;
	}
}

const char* GLTFAccessorType::name() const
{
	switch (_state)	{
		F_ENUM_NAME(SCALAR);
		F_ENUM_NAME(VEC2);
		F_ENUM_NAME(VEC3);
		F_ENUM_NAME(VEC4);
		F_ENUM_NAME(MAT2);
		F_ENUM_NAME(MAT3);
		F_ENUM_NAME(MAT4);
		F_ENUM_ASSERT_DEFAULT;
	}
}

size_t GLTFAccessorComponent::byteSize() const
{
	switch (_state) {
	case BYTE: return sizeof(int8_t);
	case UNSIGNED_BYTE: return sizeof(uint8_t);
	case SHORT: return sizeof(int16_t);
	case UNSIGNED_SHORT: return sizeof(uint16_t);
	case INT: return sizeof(int32_t);
	case UNSIGNED_INT: return sizeof(uint32_t);
	case FLOAT: return sizeof(float);
	default: F_ASSERT(false); return 1;
	}
}

const char* GLTFAccessorComponent::name() const
{
	switch (_state) {
		F_ENUM_NAME(BYTE);
		F_ENUM_NAME(UNSIGNED_BYTE);
		F_ENUM_NAME(SHORT);
		F_ENUM_NAME(UNSIGNED_SHORT);
		F_ENUM_NAME(INT);
		F_ENUM_NAME(UNSIGNED_INT);
		F_ENUM_NAME(FLOAT);
		F_ENUM_ASSERT_DEFAULT;
	}
}

const char* GLTFAttributeType::name() const
{
	switch (_state) {
		F_ENUM_NAME(POSITION);
		F_ENUM_NAME(NORMAL);
		F_ENUM_NAME(TANGENT);
		F_ENUM_NAME(TEXCOORD_0);
		F_ENUM_NAME(TEXCOORD_1);
		F_ENUM_NAME(COLOR_0);
		F_ENUM_NAME(JOINTS_0);
		F_ENUM_NAME(WEIGHTS_0);
		F_ENUM_ASSERT_DEFAULT;
	}
}

const char* GLTFPrimitiveMode::name() const
{
	switch (_state) {
		F_ENUM_NAME(POINTS);
		F_ENUM_NAME(LINES);
		F_ENUM_NAME(LINE_LOOP);
		F_ENUM_NAME(LINE_STRIP);
		F_ENUM_NAME(TRIANGLES);
		F_ENUM_NAME(TRIANGLE_STRIP);
		F_ENUM_NAME(TRIANGLE_FAN);
		F_ENUM_ASSERT_DEFAULT;
	}
}

const char* GLTFMagFilter::name() const
{
	switch (_state) {
		F_ENUM_NAME(NEAREST);
		F_ENUM_NAME(LINEAR);
		F_ENUM_ASSERT_DEFAULT;
	}
}

const char* GLTFMinFilter::name() const
{
	switch (_state) {
		F_ENUM_NAME(NEAREST);
		F_ENUM_NAME(LINEAR);
		F_ENUM_NAME(NEAREST_MIPMAP_NEAREST);
		F_ENUM_NAME(LINEAR_MIPMAP_NEAREST);
		F_ENUM_NAME(NEAREST_MIPMAP_LINEAR);
		F_ENUM_NAME(LINEAR_MIPMAP_LINEAR);
		F_ENUM_ASSERT_DEFAULT;
	}
}

const char* GLTFWrapMode::name() const
{
	switch (_state) {
		F_ENUM_NAME(REPEAT);
		F_ENUM_NAME(CLAMP_TO_EDGE);
		F_ENUM_NAME(MIRRORED_REPEAT);
		F_ENUM_ASSERT_DEFAULT;
	}
}

const char* GLTFMimeType::name() const
{
	switch (_state) {
	case IMAGE_JPEG: return "image/jpeg";
	case IMAGE_PNG:  return "image/png";

	default: F_ASSERT(false); return "(undefined)";
	}
}

const char* GLTFAlphaMode::name() const
{
	switch (_state) {
		F_ENUM_NAME(OPAQUE);
		F_ENUM_NAME(MASK);
		F_ENUM_NAME(BLEND);
		F_ENUM_ASSERT_DEFAULT;
	}
}
