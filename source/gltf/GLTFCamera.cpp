/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFCamera.h"

using namespace flow;
using std::string;


GLTFCamera::GLTFCamera(size_t index, const string& name) :
	GLTFElement(index, name),
	_zfar(1000.0f),
	_znear(0.1f)
{
}

void GLTFCamera::setZRange(float zfar, float znear)
{
	_zfar = zfar;
	_znear = znear;
}

GLTFPerspectiveCamera::GLTFPerspectiveCamera(size_t index, const string& name /* = std::string */) :
	GLTFCamera(index, name),
	_aspect(1.0f),
	_yfov(1.0f)
{
}

void GLTFPerspectiveCamera::setPerspective(float aspect, float yfov)
{
	_aspect = aspect;
	_yfov = yfov;
}

void GLTFPerspectiveCamera::addPerspectiveExtension(std::string& prop, const json& jsonData)
{
	_perspExtensions[prop] = jsonData;
}

void GLTFPerspectiveCamera::setPerspectiveExtras(const json& jsonData)
{
	_perspExtras = jsonData;
}

json GLTFPerspectiveCamera::toJSON() const
{
	json result = GLTFCamera::toJSON();

	result["type"] = "perspective";

	json perspective {
		{ "aspect", _aspect },
		{ "yfov", _yfov },
		{ "zfar", _zfar },
		{ "znear", _znear }
	};

	if (!_perspExtensions.empty()) {
		perspective["extensions"] = _perspExtensions;
	}
	if (!_perspExtras.empty()) {
		perspective["extras"] = _perspExtras;
	}

	result["perspective"] = perspective;

	return result;
}

GLTFOrthographicCamera::GLTFOrthographicCamera(size_t index, const std::string& name /* = std::string */) :
	GLTFCamera(index, name),
	_xmag(1.0f),
	_ymag(1.0f)
{
}

void GLTFOrthographicCamera::setOrthographic(float xmag, float ymag)
{
	_xmag = xmag;
	_ymag = ymag;
}

void GLTFOrthographicCamera::addOrthographicExtension(std::string& prop, const json& jsonData)
{
	_orthoExtensions[prop] = jsonData;
}

void GLTFOrthographicCamera::setOrthographicExtras(const json& jsonData)
{
	_orthoExtras = jsonData;
}

json GLTFOrthographicCamera::toJSON() const
{
	json result = GLTFCamera::toJSON();

	result["type"] = "orthographic";

	json orthographic {
		{ "xmag", _xmag },
		{ "ymag", _ymag },
		{ "zfar", _zfar },
		{ "znear", _znear }
	};

	if (!_orthoExtensions.empty()) {
		orthographic["extensions"] = _orthoExtensions;
	}
	if (!_orthoExtras.empty()) {
		orthographic["extras"] = _orthoExtras;
	}

	result["orthographic"] = orthographic;

	return result;
}
