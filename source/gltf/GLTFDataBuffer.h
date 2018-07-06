/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_DATABUFFER_H
#define _FLOWLIBS_GLTF_DATABUFFER_H

#include "library.h"
#include "GLTFBuffer.h"

//namespace flow
//{
//	class GLTFDataBuffer : public GLTFBuffer
//	{
//		GLTFBufferView* addImage(const std::string& imageFile);
//		GLTFBufferView* addData(const char* pData, size_t byteLength, bool isElementArray = false);
//
//		template<typename T>
//		GLTFAccessor* addArray(const T* pData, size_t elementCount);
//
//		template<typename T>
//		GLTFAccessor* addElementArray(const T* pData, size_t elementCount);
//
//	};
//
//	template<typename T>
//	GLTFAccessor* GLTFBuffer::addArray(const T* pData, size_t elementCount)
//	{
//		size_t byteLength = elementCount * sizeof(T);
//		auto pBufferView = addData((const char*)pData, byteLength);
//
//		auto pAccessor = _pObject->createAccessor(pBufferView);
//		pAccessor->setType<T>();
//		pAccessor->setRange(elementCount, 0);
//
//		return pAccessor;
//	}
//
//	template<typename T>
//	GLTFAccessor* GLTFBuffer::addElementArray(const T* pData, size_t elementCount)
//	{
//		size_t byteLength = elementCount * sizeof(T);
//		auto pBufferView = addData((const char*)pData, byteLength);
//
//		auto pAccessor = _pObject->createAccessor(pBufferView);
//		pAccessor->setType<T>();
//		pAccessor->setRange(elementCount, 0);
//
//		return pAccessor;
//	}
//
//	template<typename T>
//	void GLTFBuffer::_getMinMax(const T* pData, size_t count, T* pMin, T* pMax)
//	{
//		for (size_t i = 0; i < count; ++i) {
//			*pMin = flow::min(*pMin, pData[i]);
//			*pMax = flow::max(*pMax, pData[i]);
//		}
//	}
//}

#endif // _FLOWLIBS_GLTF_DATABUFFER_H