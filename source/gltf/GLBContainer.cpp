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

	const GLTFAsset::bufferVec_t& buffers = _pAsset->buffers();

	// stringify json
	string json = _pAsset->toJSON().dump(-1, ' ', true);

	// size calculations
	size_t jsonHeaderLength = sizeof(_jsonChunkHeader);
	size_t binHeaderLength = sizeof(_binChunkHeader);

	size_t jsonLength = json.size();
	size_t jsonPaddedLength = Bit::ceil4(jsonLength);

	size_t binaryChunksTotalLength = 0;
	for (size_t i = 0; i < buffers.size(); ++i) {
		binaryChunksTotalLength += Bit::ceil4(buffers[i]->byteLength()) + binHeaderLength;
	}
	size_t glbTotalLength = sizeof(_glbHeader) + jsonPaddedLength + jsonHeaderLength + binaryChunksTotalLength;

	// header
	_glbHeader.length = uint32_t(glbTotalLength);
	stream.write((char*)&_glbHeader, sizeof(_glbHeader));

	// JSON
	_jsonChunkHeader.length = uint32_t(jsonPaddedLength);
	stream.write((char*)&_jsonChunkHeader, jsonHeaderLength);
	stream.write(json.data(), jsonLength);
	stream.write((char*)&_spaces, jsonPaddedLength - jsonLength);

	// Binary buffers
	for (size_t i = 0; i < buffers.size(); ++i) {
		size_t bufferLength = buffers[i]->byteLength();
		size_t bufferPaddedLength = Bit::ceil4(bufferLength);
		_binChunkHeader.length = uint32_t(bufferPaddedLength);
		stream.write((char*)&_binChunkHeader, binHeaderLength);
		stream.write(buffers[i]->data(), bufferLength);
		stream.write((char*)&_null, bufferPaddedLength - bufferLength);
	}

	stream.close();
	return true;
}