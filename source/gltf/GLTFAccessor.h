/**
 * Flow Libs - GLTF
 *
 * @author Ralph Wiedemeier <ralph@framefactory.io>
 * @copyright (c) 2018 Frame Factory GmbH.
 */
 
#ifndef _FLOWLIBS_GLTF_ACCESSOR_H
#define _FLOWLIBS_GLTF_ACCESSOR_H
 
#include "library.h"
#include "GLTFMainElement.h"

#include "../math/Vector2T.h"
#include "../math/Vector3T.h"
#include "../math/Vector4T.h"

#include <string>
#include <vector>


namespace flow
{
	class GLTFBufferView;

	enum class GLTFAccessorType
	{
		SCALAR,
		VEC2,
		VEC3,
		VEC4,
		MAT2,
		MAT3,
		MAT4
	};

	enum class GLTFAccessorComponent
	{
		BYTE = 0x1400,
		UNSIGNED_BYTE = 0x1401,
		SHORT = 0x1402,
		UNSIGNED_SHORT = 0x1403,
		INT = 0x1404,
		UNSIGNED_INT = 0x1405,
		FLOAT = 0x1406
	};

	class GLTFAccessor : public GLTFMainElement
	{
		friend class GLTFObject;

	protected:
		GLTFAccessor(size_t index, const std::string& name = std::string{});
		virtual ~GLTFAccessor();

	public:
		void setBufferView(const GLTFBufferView* pBufferView);

		void setType(GLTFAccessorType type, GLTFAccessorComponent component, bool normalized = false);
		void setRange(size_t elementCount, size_t byteOffset, size_t byteStride = 0);
		void setMin(const std::vector<double>& min);
		void setMax(const std::vector<double>& max);

		GLTFAccessorType type() const { return _type; }
		GLTFAccessorComponent component() const { return _componentType; }
		size_t count() const { return _count; }
		size_t byteOffset() const { return _byteOffset; }
		size_t byteStride() const { return _byteStride; }
		const std::vector<double>& min() const { return _min; }
		const std::vector<double>& max() const { return _max; }

		virtual json toJSON() const;

	private:
		const char* _typeName(GLTFAccessorType type) const;
		const size_t _componentCount(GLTFAccessorType type) const;
		const size_t _componentSize(GLTFAccessorComponent componentType) const;

		const GLTFBufferView* _pBufferView;
		GLTFAccessorType _type;
		GLTFAccessorComponent _componentType;
		bool _normalized;
		size_t _count;
		size_t _byteOffset;
		size_t _byteStride;
		std::vector<double> _min;
		std::vector<double> _max;
	};
}
 
#endif // _FLOWLIBS_GLTF_ACCESSOR_H
