/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#include "GLTFAsset.h"

using namespace flow;
using std::string;

GLTFAsset::GLTFAsset(GLTFVersion version /* = GLTFVersion::GLTF_2_0 */) :
	_version(version),
	_minVersion(GLTFVersion::UNDEFINED)
{
}

void GLTFAsset::setCopyright(const string& copyright)
{
	_copyright = copyright;
}

void GLTFAsset::setGenerator(const string& generator)
{
	_generator = generator;
}

void GLTFAsset::setVersion(GLTFVersion version)
{
	_version = version;
}

void GLTFAsset::setMinVersion(GLTFVersion minVersion)
{
	_minVersion = minVersion;
}

json GLTFAsset::toJSON() const
{
	json result = GLTFElement::toJSON();

	result["version"] = _getVersionText(_version);

	if (!_copyright.empty()) {
		result["copyright"] = _copyright;
	}
	if (!_generator.empty()) {
		result["generator"] = _generator;
	}
	if (_minVersion != GLTFVersion::UNDEFINED) {
		result["minVersion"] = _getVersionText(_minVersion);
	}

	return result;
}

const char* GLTFAsset::_getVersionText(GLTFVersion version) const
{
	switch (version) {
	case GLTFVersion::UNDEFINED: return "2.0";
	case GLTFVersion::GLTF_1_0: return "1.0";
	case GLTFVersion::GLTF_2_0:  return "2.0";
	default: return "2.0";
	}
}