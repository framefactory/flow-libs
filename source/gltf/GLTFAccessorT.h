/**
 * Flow Libs - GLTF
 *
 * @author Ralph Wiedemeier <ralph@framefactory.io>
 * @copyright (c) 2018 Frame Factory GmbH.
 */

#ifndef _FLOWLIBS_GLTF_ACCESSORT_H
#define _FLOWLIBS_GLTF_ACCESSORT_H

#include "library.h"
#include "GLTFAccessor.h"
#include "GLTFConstants.h"

#include <string>
#include <limits>

namespace flow
{
	class GLTFBuffer;

	template <typename T>
	class GLTFAccessorT : public GLTFAccessor
	{
		friend class GLTFAsset;

	protected:
		GLTFAccessorT(size_t index, GLTFAccessorType type, std::string& name = std::string{}) :
			GLTFAccessor(index, type, name) { }
		
		virtual ~GLTFAccessorT() { }

	public:
		T * allocateVertexData(GLTFBuffer* pBuffer, size_t elementCount);
		T * allocateIndexData(GLTFBuffer* pBuffer, size_t elementCount);
		void addVertexData(GLTFBuffer* pBuffer, const T* pData, size_t elementCount);
		void addIndexData(GLTFBuffer* pBuffer, const T* pData, size_t elementCount);
		void updateBounds(const T* pData = nullptr);

		std::vector<T>& min() { return _min; }
		const std::vector<T>& min() const { return _min; }

		std::vector<T>& max() { return _max }
		const std::vector<T>& max() const { return _max }

		virtual GLTFAccessorComponent component() const { return GLTFAccessorComponent::type<T>(); }
		
		virtual json toJSON() const;

	protected:
		std::vector<T> _min;
		std::vector<T> _max;
	};

	template<typename T>
	T* GLTFAccessorT<T>::allocateVertexData(GLTFBuffer* pBuffer, size_t elementCount)
	{
		_count = elementCount;

		size_t byteLength = elementCount * _type.componentCount() * sizeof(T);
		return (T*)allocateData(pBuffer, byteLength, GLTFBufferViewTarget::ARRAY_BUFFER);
	}

	template<typename T>
	T* GLTFAccessorT<T>::allocateIndexData(GLTFBuffer* pBuffer, size_t elementCount)
	{
		_count = elementCount;

		size_t byteLength = elementCount * _type.componentCount() * sizeof(T);
		return (T*)allocateData(pBuffer, byteLength, GLTFBufferViewTarget::ELEMENT_ARRAY_BUFFER);
	}

	template<typename T>
	void GLTFAccessorT<T>::addVertexData(GLTFBuffer* pBuffer, const T* pData, size_t elementCount)
	{
		_count = elementCount;

		size_t byteLength = elementCount * _type.componentCount() * sizeof(T);
		addData(pBuffer, (const char*)pData, byteLength, GLTFBufferViewTarget::ARRAY_BUFFER);
	}

	template<typename T>
	void GLTFAccessorT<T>::addIndexData(GLTFBuffer* pBuffer, const T* pData, size_t elementCount)
	{
		_count = elementCount;

		size_t byteLength = elementCount * _type.componentCount() * sizeof(T);
		addData(pBuffer, (const char*)pData, byteLength, GLTFBufferViewTarget::ELEMENT_ARRAY_BUFFER);
	}

	template<typename T>
	void GLTFAccessorT<T>::updateBounds(const T* pData /* = nullptr */)
	{
		if (!pData) {
			pData = (const T*)data();
			if (!pData) {
				throw std::exception("no data source specified");
			}
		}

		size_t n = _count;
		size_t cc = _type.componentCount();

		_max.resize(cc);
		_min.resize(cc);

		for (size_t j = 0; j < cc; ++j) {
			_max[j] = std::numeric_limits<T>::lowest();
			_min[j] = std::numeric_limits<T>::max();
		}

		for (size_t i = 0; i < n; ++i) {
			const T* pElem = pData + i * cc;
			for (size_t j = 0; j < cc; ++j) {
				_max[j] = flow::max(_max[j], pElem[j]);
				_min[j] = flow::min(_min[j], pElem[j]);
			}
		}
	}

	template<typename T>
	json GLTFAccessorT<T>::toJSON() const
	{
		json result = GLTFAccessor::toJSON();
		
		result["componentType"] = (int)component();

		if (!_min.empty()) {
			result["min"] = _min;
		}
		if (!_max.empty()) {
			result["max"] = _max;
		}

		return result;
	}
}

#endif // _FLOWLIBS_GLTF_ACCESSORT_H