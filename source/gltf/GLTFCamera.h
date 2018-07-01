/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_CAMERA_H
#define _FLOWLIBS_GLTF_CAMERA_H

#include "GLTFElement.h"


namespace flow
{
	class GLTFCamera : public GLTFElement
	{
		friend class GLTFAsset;

	public:
		enum Type {
			Perspective,
			Orthographic
		};

	protected:
		GLTFCamera(size_t index);
		virtual ~GLTFCamera();

	public:
		void setPerspective(float aspect, float yfov, float zfar, float znear);
		void setOrthographic(float xmag, float ymag, float zfar, float znear);

		virtual json toJSON() const;

	private:
		Type _type;
		float _aspect;
		float _yfov;
		float _xmag;
		float _ymag;
		float _zfar;
		float _znear;
	};
}

#endif // _FLOWLIBS_GLTF_CAMERA_H
