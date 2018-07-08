/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLBContainer.h"

#include "GLTFAsset.h"
#include "GLTFBuffer.h"

#include "../core/Bit.h"

#include <iostream>
#include <fstream>

using namespace flow;
using std::string;
using std::vector;
using std::ofstream;
using std::ios;


GLBContainer::GLBContainer(const GLTFAsset* pAsset) :
	_pAsset(pAsset)
{
}

bool GLBContainer::save(const string& filePath) const
{
	ofstream stream(filePath, ios::out | ios::binary);
	if (!stream.is_open()) {
		return false;
	}

	// get first binary buffer
	const GLTFAsset::bufferVec_t& buffers = _pAsset->buffers();
	if (buffers.empty()) {
		return false;
	}

	const GLTFBuffer* pBinaryBuffer = buffers[0];

	// stringify json
	string json = _pAsset->toJSON().dump(-1, ' ', true);

	// size calculations
	size_t jsonHeaderLength = sizeof(_jsonChunkHeader);
	size_t binHeaderLength = sizeof(_binChunkHeader);

	size_t jsonLength = json.size();
	size_t jsonPaddedLength = Bit::ceil4(jsonLength);

	size_t binaryPaddedLength = Bit::ceil4(pBinaryBuffer->byteLength());
	size_t glbTotalLength = sizeof(_glbHeader)
		+ jsonPaddedLength + jsonHeaderLength + binaryPaddedLength + binHeaderLength;

	// header
	_glbHeader.length = uint32_t(glbTotalLength);
	stream.write((char*)&_glbHeader, sizeof(_glbHeader));

	// add JSON chunk
	_jsonChunkHeader.length = uint32_t(jsonPaddedLength);
	stream.write((char*)&_jsonChunkHeader, jsonHeaderLength);
	stream.write(json.data(), jsonLength);
	stream.write((char*)&_spaces, jsonPaddedLength - jsonLength);

	// add binary chunk
	size_t bufferLength = pBinaryBuffer->byteLength();
	size_t bufferPaddedLength = Bit::ceil4(bufferLength);
	_binChunkHeader.length = uint32_t(bufferPaddedLength);
	stream.write((char*)&_binChunkHeader, binHeaderLength);
	stream.write(pBinaryBuffer->data(), bufferLength);
	stream.write((char*)&_null, bufferPaddedLength - bufferLength);

	stream.close();
	return true;
}