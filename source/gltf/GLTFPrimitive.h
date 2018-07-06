/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_PRIMITIVE_H
#define _FLOWLIBS_GLTF_PRIMITIVE_H

#include "library.h"
#include "GLTFElement.h"
#include "GLTFConstants.h"

#include <string>
#include <vector>


namespace flow
{
	class GLTFMaterial;
	class GLTFAccessor;

	struct GLTFAttribute
	{
		GLTFAttributeType type;
		const GLTFAccessor* pAccessor;
	};

	class F_GLTF_EXPORT GLTFPrimitive : public GLTFElement
	{
	public:
		GLTFPrimitive(GLTFPrimitiveMode mode = GLTFPrimitiveMode::TRIANGLES, const GLTFMaterial* pMaterial = nullptr);
		virtual ~GLTFPrimitive() {}

		typedef std::vector<GLTFAttribute> attributeVec_t;
		typedef std::vector<attributeVec_t> targetVec_t;

		void setMode(GLTFPrimitiveMode mode);
		void setMaterial(const GLTFMaterial* pMaterial);

		void setIndices(const GLTFAccessor* pAccessor);
		void addAttribute(GLTFAttributeType type, const GLTFAccessor* pAccessor);
		void addTargetAttribute(size_t index, GLTFAttributeType type, const GLTFAccessor* pAccessor);

		void addPositions(const GLTFAccessor* pAccessor);
		void addNormals(const GLTFAccessor* pAccessor);
		void addTexCoords(const GLTFAccessor* pAccessor);

		GLTFPrimitiveMode mode() const { return _mode; }
		const GLTFMaterial* material() const { return _pMaterial; }
		const GLTFAccessor* indices() const { return _pIndicesAccessor; }
		const attributeVec_t& attributes() const { return _attributes; }
		const targetVec_t& targets() const { return _targets; }

		virtual json toJSON() const;

	private:
		const char* _attribName(GLTFAttributeType type) const;

		GLTFPrimitiveMode _mode;
		const GLTFMaterial* _pMaterial;
		const GLTFAccessor* _pIndicesAccessor;

		attributeVec_t _attributes;
		targetVec_t _targets;
	};
}

#endif // _FLOWLIBS_GLTF_PRIMITIVE_H