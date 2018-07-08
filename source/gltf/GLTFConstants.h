/**
 * Flow Libs - glTF
 *
 * @author Ralph Wiedemeier <ralph@framefactory.io>
 * @copyright (c) 2018 Frame Factory GmbH.
 */
 
#ifndef _FLOWLIBS_GLTF_CONSTANTS_H
#define _FLOWLIBS_GLTF_CONSTANTS_H

#include "library.h"

namespace flow
{
	struct GLTFVersion
	{
		enum enum_type
		{
			UNDEFINED,
			GLTF_1_0,
			GLTF_2_0
		};
	
		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFVersion, UNDEFINED);
	};

	struct GLTFBufferViewTarget
	{
		enum enum_type
		{
			UNDEFINED            = 0x0000,
			ARRAY_BUFFER         = 0x8892,
			ELEMENT_ARRAY_BUFFER = 0x8893
		};
	
		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFBufferViewTarget, UNDEFINED);
	};

	struct GLTFAccessorType
	{
		enum enum_type
		{
			SCALAR,
			VEC2,
			VEC3,
			VEC4,
			MAT2,
			MAT3,
			MAT4
		};

		size_t componentCount() const;
	
		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFAccessorType, SCALAR);
	};

	struct GLTFAccessorComponent
	{
		enum enum_type
		{
			BYTE           = 0x1400,
			UNSIGNED_BYTE  = 0x1401,
			SHORT          = 0x1402,
			UNSIGNED_SHORT = 0x1403,
			INT            = 0x1404,
			UNSIGNED_INT   = 0x1405,
			FLOAT          = 0x1406
		};

		size_t byteSize() const;

		template<typename T>
		static GLTFAccessorComponent type() { F_ASSERT(false); return BYTE; }

		template<> static GLTFAccessorComponent type<int8_t>() { return BYTE; }
		template<> static GLTFAccessorComponent type<uint8_t>() { return UNSIGNED_BYTE; }
		template<> static GLTFAccessorComponent type<int16_t>() { return SHORT; }
		template<> static GLTFAccessorComponent type<uint16_t>() { return UNSIGNED_SHORT; }
		template<> static GLTFAccessorComponent type<int32_t>() { return INT; }
		template<> static GLTFAccessorComponent type<uint32_t>() { return UNSIGNED_INT; }
		template<> static GLTFAccessorComponent type<float>() { return FLOAT; }
	
		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFAccessorComponent, BYTE);
	};

	struct GLTFAttributeType
	{
		enum enum_type
		{
			POSITION,
			NORMAL,
			TANGENT,
			TEXCOORD_0,
			TEXCOORD_1,
			COLOR_0,
			JOINTS_0,
			WEIGHTS_0
		};

		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFAttributeType, POSITION);
	};

	struct GLTFPrimitiveMode
	{
		enum enum_type
		{
			POINTS = 0,
			LINES = 1,
			LINE_LOOP = 2,
			LINE_STRIP = 3,
			TRIANGLES = 4,
			TRIANGLE_STRIP = 5,
			TRIANGLE_FAN = 6
		};

		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFPrimitiveMode, TRIANGLES);
	};

	struct GLTFMagFilter
	{
		enum enum_type
		{
			NEAREST = 9728,
			LINEAR = 9729
		};

		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFMagFilter, LINEAR);
	};

	struct GLTFMinFilter
	{
		enum enum_type
		{
			NEAREST = 9728,
			LINEAR = 9729,
			NEAREST_MIPMAP_NEAREST = 9984,
			LINEAR_MIPMAP_NEAREST = 9985,
			NEAREST_MIPMAP_LINEAR = 9986,
			LINEAR_MIPMAP_LINEAR = 9987
		};

		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFMinFilter, LINEAR_MIPMAP_LINEAR);
	};

	struct GLTFWrapMode
	{
		enum enum_type
		{
			REPEAT = 10497,
			CLAMP_TO_EDGE = 33071,
			MIRRORED_REPEAT = 33648
		};

		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFWrapMode, REPEAT);
	};

	struct GLTFMimeType
	{
		enum enum_type
		{
			IMAGE_JPEG,
			IMAGE_PNG
		};

		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFMimeType, IMAGE_JPEG);
	};
	
	struct GLTFAlphaMode
	{
		enum enum_type
		{
			OPAQUE,
			MASK,
			BLEND
		};

		F_DECLARE_ENUM(F_GLTF_EXPORT, GLTFAlphaMode, OPAQUE);
	};
}

 
#endif // _FLOWLIBS_GLTF_CONSTANTS_H