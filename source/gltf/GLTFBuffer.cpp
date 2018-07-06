/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFBuffer.h"
#include "GLTFBufferView.h"
#include "GLTFAccessor.h"
#include "GLTFObject.h"

#include <fstream>
#include <limits>

using namespace flow;
using std::string;
using std::ifstream;
using std::ios;
using std::numeric_limits;


static float _fMax = numeric_limits<float>::max();
static float _fMin = -_fMax;
static uint32_t _iMax = numeric_limits<uint32_t>::max();
static uint32_t _iMin = 0;
static Vector2f _v2Min{ _fMin, _fMin };
static Vector2f _v2Max{ _fMax, _fMax };
static Vector3f _v3Min{ _fMin, _fMin, _fMin };
static Vector3f _v3Max{ _fMax, _fMax, _fMax };


GLTFBuffer::GLTFBuffer(GLTFObject* pObject, size_t index, const string& name /* = string{} */) :
	GLTFMainElement(index, name),
	_pObject(pObject),
	_byteLength(0)
{
}

void GLTFBuffer::setByteLength(size_t byteLength)
{
	_byteLength = byteLength;
}

void GLTFBuffer::setUri(const string& uri)
{
	_uri = uri;
}



json GLTFBuffer::toJSON() const
{
	json result = GLTFMainElement::toJSON();

	result["byteLength"] = _byteLength;

	if (!_uri.empty()) {
		result["uri"] = _uri;
	}

	return result;
}

