/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_CAMERA_H
#define _FLOWLIBS_GLTF_CAMERA_H

#include "GLTFElement.h"
#include <string>


namespace flow
{
	class GLTFCamera : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFCamera(size_t index, const std::string& name);
		virtual ~GLTFCamera() { }

	public:
		void setZRange(float zfar, float znear);

		float zfar() const { return _zfar; }
		float znear() const { return _znear; }

	protected:
		float _zfar;
		float _znear;
	};

	class GLTFPerspectiveCamera : public GLTFCamera
	{
	protected:
		GLTFPerspectiveCamera(size_t index, const std::string& name = std::string{});
		~GLTFPerspectiveCamera() { }

	public:
		void setPerspective(float aspect, float yfov);
		void addPerspectiveExtension(std::string& prop, const json& jsonData);
		void setPerspectiveExtras(const json& jsonData);

		float aspect() const { return _aspect; }
		float yfov() const { return _yfov; }

		virtual json toJSON() const;

	private:
		float _aspect;
		float _yfov;
		json _perspExtensions;
		json _perspExtras;
	};

	class GLTFOrthographicCamera : public GLTFCamera
	{
	protected:
		GLTFOrthographicCamera(size_t index, const std::string& name = std::string{});
		~GLTFOrthographicCamera() { }

	public:
		void setOrthographic(float xmag, float ymag);
		void addOrthographicExtension(std::string& prop, const json& jsonData);
		void setOrthographicExtras(const json& jsonData);

		float xmag() const { return _xmag; }
		float ymag() const { return _ymag; }

		virtual json toJSON() const;

	private:
		float _xmag;
		float _ymag;
		json _orthoExtensions;
		json _orthoExtras;
	};
}

#endif // _FLOWLIBS_GLTF_CAMERA_H
