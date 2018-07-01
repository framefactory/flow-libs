/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFCamera.h"

using namespace flow;


GLTFCamera::GLTFCamera(size_t index) :
	GLTFElement(index)
{
}

GLTFCamera::~GLTFCamera()
{
}

void GLTFCamera::setPerspective(float aspect, float yfov, float zfar, float znear)
{
	_type = Type::Perspective;
	_aspect = aspect;
	_yfov = yfov;
	_zfar = zfar;
	_znear = znear;
}

void GLTFCamera::setOrthographic(float xmag, float ymag, float zfar, float znear)
{
	_type = Type::Orthographic;
	_xmag = xmag;
	_ymag = ymag;
	_zfar = zfar;
	_znear = znear;
}

json GLTFCamera::toJSON() const
{
	if (_type == Type::Perspective) {
		return json({
			{ "type", "perspective" },
			{ "perspective", {
				{ "aspectRatio", _aspect },
				{ "yfov", _yfov },
				{ "zfar", _zfar },
				{ "znear", _znear }
			}}
		});
	}
	else {
		return json({
			{ "type", "orthographic" },
			{ "orthographic", {
				{ "xmag", _xmag },
				{ "ymag", _ymag },
				{ "zfar", _zfar },
				{ "znear", _znear }
			}}
		});
	}
}
