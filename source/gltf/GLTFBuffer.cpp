/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFBuffer.h"
#include "GLTFBufferView.h"
#include "GLTFAccessor.h"
#include "GLTFAsset.h"

#include <fstream>
#include <cstring>

using namespace flow;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;


GLTFBuffer::GLTFBuffer(GLTFAsset* pAsset, size_t index, const string& name /* = string{} */) :
	GLTFMainElement(index, name),
	_pAsset(pAsset)
{
}

GLTFBufferView* GLTFBuffer::addData(const char* pData, size_t byteLength)
{
	auto pBufferView = allocate(byteLength);
	std::memcpy(pBufferView->data(), pData, byteLength);

	return pBufferView;
}

GLTFBufferView* GLTFBuffer::addImage(const string& imageFilePath)
{
	ifstream stream(imageFilePath, ios::in | ios::ate | ios::binary);
	if (!stream.is_open()) {
		return nullptr;
	}

	size_t byteLength = (size_t)stream.tellg();

	auto pBufferView = allocate(byteLength);
	
	stream.seekg(0);
	stream.read(pBufferView->data(), byteLength);
	stream.close();

	return pBufferView;
}

GLTFBufferView* GLTFBuffer::allocate(size_t byteLength)
{
	size_t byteStart = _buffer.size();
	size_t newBufferSize = byteStart + byteLength;

	_buffer.resize(newBufferSize);

	auto pBufferView = _pAsset->_createBufferView();
	pBufferView->_set(this, byteStart, byteLength);
	return pBufferView;
}


void GLTFBuffer::setUri(const string& uri)
{
	_uri = uri;
}

bool GLTFBuffer::save(const string& bufferFilePath)
{
	ofstream stream(bufferFilePath, ios::out | ios::binary);
	if (!stream.is_open()) {
		return false;
	}

	stream.write(_buffer.data(), _buffer.size());
	stream.close();
	return true;
}

json GLTFBuffer::toJSON() const
{
	json result = GLTFMainElement::toJSON();

	result["byteLength"] = _buffer.size();

	if (!_uri.empty()) {
		result["uri"] = _uri;
	}

	return result;
}

