/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFImage.h"
#include "GLTFBufferView.h"

using namespace flow;
using std::string;


GLTFImage::GLTFImage(size_t index, const string& name /* = std::string{} */) :
	GLTFMainElement(index, name),
	_pBufferView(nullptr),
	_mimeType(GLTFMimeType::IMAGE_JPEG)
{
}

void GLTFImage::setUri(const string& uri)
{
	_uri = uri;
	_pBufferView = nullptr;
	_mimeType = GLTFMimeType::IMAGE_JPEG;
}

void GLTFImage::setBufferView(const GLTFBufferView* pBufferView, GLTFMimeType mimeType)
{
	_uri = string{};
	_pBufferView = pBufferView;
	_mimeType = mimeType;
}

json GLTFImage::toJSON() const
{
	json result = GLTFMainElement::toJSON();

	if (_pBufferView) {
		result["bufferView"] = _pBufferView->index();
		result["mimeType"] = _getMimeTypeName(_mimeType);
	}
	else {
		result["uri"] = _uri;
	}

	return result;
}

const char* GLTFImage::_getMimeTypeName(GLTFMimeType mimeType) const
{
	switch (mimeType) {
	case GLTFMimeType::IMAGE_JPEG:
		return "image/jpeg";
	case GLTFMimeType::IMAGE_PNG:
	default:
		return "image/png";
	}
}