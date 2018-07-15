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
		/// Protected constructor. Meshes must be created using the factory methods in GLTFAsset.
		GLTFMesh(size_t index, const std::string& name = std::string{});
		/// Virtual destructor.
		virtual ~GLTFMesh() { }

	public:
		typedef std::vector<GLTFPrimitive> primitiveVec_t;
		typedef std::vector<float> weightVec_t;

		/// Adds the given primitive to the mesh.
		void addPrimitive(const GLTFPrimitive& primitive);
		/// Creates a new primitive using the given mode and material and returns a reference to it.
		GLTFPrimitive& createPrimitive(GLTFPrimitiveMode mode, const GLTFMaterial* pMaterial = nullptr);
		void addWeight(float weight);
		/// Sets the material for all primitives of the mesh.
		void setMaterial(const GLTFMaterial* pMaterial);

		/// Returns a const reference to the vector of primitives in this mesh.
		const primitiveVec_t& primitives() const { return _primitives; }
		/// Returns a const reference to the vector of weights in this mesh.
		const weightVec_t& weights() const { return _weights; }

		virtual json toJSON() const;

	private:
		primitiveVec_t _primitives;
		weightVec_t _weights;
	};
}

#endif // _FLOWLIBS_GLTF_MESH_H
