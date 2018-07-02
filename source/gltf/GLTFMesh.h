/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_MESH_H
#define _FLOWLIBS_GLTF_MESH_H

#include "GLTFElement.h"

#include <string>
#include <vector>


namespace flow
{
	class GLTFMaterial;
	class GLTFAccessor;

	enum class GLTFAttributeType
	{
		POSITION,
		NORMAL,
		TANGENT,
		TEXCOORD_0,
		TEXCOORD_1,
		COLOR_0,
		JOINTS_0,
		WEIGHTS_0
	};

	struct GLTFAttribute
	{
		GLTFAttributeType type;
		const GLTFAccessor* pAccessor;
	};

	struct Target
	{
		std::vector<GLTFAttribute> attributes;
	};

	enum class GLTFPrimitiveMode
	{
		POINTS         = 0,
		LINES          = 1,
		LINE_LOOP      = 2,
		LINE_STRIP     = 3,
		TRIANGLES      = 4,
		TRIANGLE_STRIP = 5,
		TRIANGLE_FAN   = 6
	};

	class GLTFPrimitive : public GLTFElement
	{
		friend class GLTFMesh;

	protected:
		GLTFPrimitive(size_t index);
		virtual ~GLTFPrimitive() { }

	public:
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

	class GLTFMesh : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFMesh(size_t index, const std::string& name = std::string{});
		virtual ~GLTFMesh();

	public:
		typedef std::vector<GLTFPrimitive*> primitiveVec_t;
		typedef std::vector<float> weightVec_t;

		GLTFPrimitive* createPrimitive(GLTFPrimitiveMode mode, const GLTFMaterial* pMaterial = nullptr);
		void addWeight(float weight);

		const primitiveVec_t& primitives() const { return _primitives; }
		const weightVec_t& weights() const { return _weights; }

		virtual json toJSON() const;

	private:
		primitiveVec_t _primitives;
		weightVec_t _weights;
	};
}

#endif // _FLOWLIBS_GLTF_MESH_H
