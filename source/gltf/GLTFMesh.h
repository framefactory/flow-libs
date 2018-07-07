/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_MESH_H
#define _FLOWLIBS_GLTF_MESH_H

#include "library.h"
#include "GLTFMainElement.h"
#include "GLTFPrimitive.h"

#include <string>
#include <vector>


namespace flow
{
	class GLTFMaterial;
	class GLTFPrimitive;
	

	class F_GLTF_EXPORT GLTFMesh : public GLTFMainElement
	{
		friend class GLTFAsset;

	protected:
		GLTFMesh(size_t index, const std::string& name = std::string{});
		virtual ~GLTFMesh() { }

	public:
		typedef std::vector<GLTFPrimitive> primitiveVec_t;
		typedef std::vector<float> weightVec_t;

		void addPrimitive(const GLTFPrimitive& primitive);
		GLTFPrimitive& createPrimitive(GLTFPrimitiveMode mode, const GLTFMaterial* pMaterial = nullptr);
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
