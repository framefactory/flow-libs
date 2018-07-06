/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFDataBuffer.h"


//GLTFBufferView* GLTFBuffer::addImage(const string& imageFile)
//{
//	std::ifstream stream(imageFile, ios::in | ios::ate | ios::binary);
//	size_t byteLength = (size_t)stream.tellg();
//
//	size_t byteStart = _byteLength;
//	_byteLength += byteLength;
//	_resizeBuffer(_byteLength);
//
//	char* pDest = ((char*)_buffer.data()) + byteStart;
//	stream.seekg(0);
//	stream.read(pDest, byteLength);
//
//	auto pBufferView = _pObject->createBufferView(this);
//	pBufferView->setView(byteStart, byteLength);
//	return pBufferView;
//}
//
//GLTFBufferView* GLTFBuffer::addData(const char* pData, size_t byteLength, bool isElementArray /* = false */)
//{
//	size_t byteStart = _byteLength;
//	_byteLength += byteLength;
//	_resizeBuffer(_byteLength);
//
//	char* pDest = ((char*)_buffer.data()) + byteStart;
//	std::memcpy(pDest, pData, byteLength);
//
//	auto pBufferView = _pObject->createBufferView(this);
//	pBufferView->setView(byteStart, byteLength);
//	pBufferView->setTarget(isElementArray ? GLTFBufferTarget::ELEMENT_ARRAY_BUFFER : GLTFBufferTarget::ARRAY_BUFFER);
//	return pBufferView;
//}
//
//void GLTFBuffer::_resizeBuffer(size_t byteLength)
//{
//	size_t size = byteLength / sizeof(size_t);
//	_buffer.resize(size);
//	_byteLength = byteLength;
//}
