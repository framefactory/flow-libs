/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_MESH_H
#define _FLOWLIBS_GLTF_MESH_H

#include "GLTFElement.h"
#include <vector>

namespace flow
{
	class GLTFMaterial;
	class GLTFAccessor;

	struct GLTFAttribute
	{
		enum Type {
			POSITION,
			NORMAL,
			TANGENT,
			TEXCOORD_0,
			TEXCOORD_1,
			COLOR_0,
			JOINTS_0,
			WEIGHTS_0
		};

		Type type;
		const GLTFAccessor* pAccessor;
	};

	struct Target
	{
		std::vector<GLTFAttribute> attributes;
	};

	class GLTFPrimitive : public GLTFElement
	{
		friend class GLTFMesh;

	public:
		enum Mode {
			POINTS    = 0x0000,
			LINES     = 0x0001,
			TRIANGLES = 0x0004
		};

	protected:
		GLTFPrimitive(size_t index, Mode mode, const GLTFMaterial* pMaterial = nullptr);
		virtual ~GLTFPrimitive();

	public:
		void setMode(Mode mode);
		void setMaterial(const GLTFMaterial* pMaterial);

		void setIndices(const GLTFAccessor* pAccessor);
		void addAttribute(GLTFAttribute::Type type, const GLTFAccessor* pAccessor);
		void addTargetAttribute(size_t index, GLTFAttribute::Type type, const GLTFAccessor* pAccessor);

		void addPositions(const GLTFAccessor* pAccessor);
		void addNormals(const GLTFAccessor* pAccessor);
		void addTexCoords(const GLTFAccessor* pAccessor);

		virtual json toJSON() const;

	private:
		const char* _attribName(GLTFAttribute::Type type) const;

		Mode _mode;
		const GLTFMaterial* _pMaterial;
		const GLTFAccessor* _pIndicesAccessor;

		typedef std::vector<GLTFAttribute> attributeVec_t;
		attributeVec_t _attributes;
		std::vector<attributeVec_t> _targets;
	};

	class GLTFMesh : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFMesh(size_t index);
		virtual ~GLTFMesh();

	public:
		GLTFPrimitive* createPrimitive(GLTFPrimitive::Mode mode, const GLTFMaterial* pMaterial = nullptr);
		void addWeight(float weight);

		virtual json toJSON() const;

	private:
		typedef std::vector<GLTFPrimitive*> primitiveVec_t;
		primitiveVec_t _primitives;
		std::vector<float> _weights;
	};
}

#endif // _FLOWLIBS_GLTF_MESH_H
