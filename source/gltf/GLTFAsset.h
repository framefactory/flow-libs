/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_ASSET_H
#define _FLOWLIBS_GLTF_ASSET_H

#include "library.h"
#include "GLTFElement.h"

#include <string>

namespace flow
{
	enum class GLTFVersion
	{
		UNDEFINED,
		GLTF_1_0,
		GLTF_2_0
	};

	class GLTFAsset : public GLTFElement
	{
	public:
		GLTFAsset(GLTFVersion version = GLTFVersion::GLTF_2_0);
		virtual ~GLTFAsset() { }

		void setCopyright(const std::string& copyright);
		void setGenerator(const std::string& generator);
		void setVersion(GLTFVersion version);
		void setMinVersion(GLTFVersion minVersion);

		const std::string& copyright() const { return _copyright; }
		const std::string& generator() const { return _generator; }
		GLTFVersion version() const { return _version; }
		GLTFVersion minVersion() const { return _minVersion; }

		virtual json toJSON() const;

	private:
		const char* _getVersionText(GLTFVersion version) const;

		std::string _copyright;
		std::string _generator;
		GLTFVersion _version;
		GLTFVersion _minVersion;
	};
}

#endif // _FLOWLIBS_GLTF_ASSET_H
