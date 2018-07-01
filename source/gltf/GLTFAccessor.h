/**
 * Flow Libs - GLTF
 *
 * @author Ralph Wiedemeier <ralph@framefactory.io>
 * @copyright (c) 2018 Frame Factory GmbH.
 */
 
#ifndef _FLOWLIBS_GLTF_ACCESSOR_H
#define _FLOWLIBS_GLTF_ACCESSOR_H
 
#include "GLTFElement.h"
#include <vector>


namespace flow
{
	class GLTFBufferView;

	class GLTFAccessor : public GLTFElement
	{
		friend class GLTFAsset;

	public:
		enum Type {
			SCALAR,
			VEC2,
			VEC3,
			VEC4,
			MAT2,
			MAT3,
			MAT4
		};

		enum ComponentType {
			BYTE           = 0x1400,
			UNSIGNED_BYTE  = 0x1401,
			SHORT          = 0x1402,
			UNSIGNED_SHORT = 0x1403,
			INT            = 0x1404,
			UNSIGNED_INT   = 0x1405,
			FLOAT          = 0x1406
		};

	protected:
		GLTFAccessor(size_t index, const GLTFBufferView* pView);
		virtual ~GLTFAccessor();

	public:
		void setType(Type type, ComponentType componentType);
		void setAccess(size_t byteOffset, size_t byteStride);

		virtual json toJSON() const;

	private:
		const char* typeName(Type type) const;
		const size_t componentCount(Type type) const;
		const size_t componentSize(ComponentType componentType) const;
		//json vecToArray(const std::vector<float>& vector) const;

		const GLTFBufferView* _pBufferView;
		Type _type;
		ComponentType _componentType;
		size_t _count;
		size_t _byteOffset;
		size_t _byteStride;
		std::vector<float> _min;
		std::vector<float> _max;
	};
}
 
#endif // _FLOWLIBS_GLTF_ACCESSOR_H
