/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_DRACOEXTENSION_H
#define _FLOWLIBS_GLTF_DRACOEXTENSION_H

#include "library.h"
#include "GLTFExtension.h"
#include "GLTFConstants.h"

#include "../core/json.h"
#include <string>

namespace draco
{
	class Mesh;
	class DataBuffer;
}

namespace flow
{
	class GLTFBuffer;
	class GLTFBufferView;
	class GLTFPrimitive;
	class GLTFAccessor;

	struct GLTFDracoOptions
	{
		GLTFDracoOptions();

		int positionQuantizationBits;
		int texCoordsQuantizationBits;
		int normalsQuantizationBits;
		int genericQuantizationBits;
		bool stripNormals;
		bool stripTexCoords;
		bool stripGeneric;
		int compressionLevel;
	};

	class F_GLTF_EXPORT GLTFDracoExtension : public GLTFExtension
	{
	public:
		struct attribute_t
		{
			GLTFAttributeType type;
			int index;
		};

		typedef std::vector<attribute_t> attributeVec_t;

		GLTFDracoExtension();
		virtual ~GLTFDracoExtension();

		bool encode(GLTFPrimitive* pPrimitive, GLTFBuffer* pCompressedBuffer);
		void setOptions(const GLTFDracoOptions& options);

		GLTFDracoOptions& options() { return _dracoOptions; }
		const GLTFDracoOptions& options() const { return _dracoOptions; }
		const GLTFBufferView* bufferView() const { return _pBufferView; }
		const attributeVec_t attributes() const { return _attributes; }

		virtual const char* name() const;
		virtual json toJSON() const;

	private:
		bool _encodeMeshToBuffer(GLTFBuffer* pCompressedBuffer);
		void _addFaces(const GLTFAccessor* pIndicesAccessor);
		int _addAttribute(const GLTFAccessor* pAccessor, GLTFAttributeType attribType);

		GLTFDracoOptions _dracoOptions;
		GLTFBufferView* _pBufferView;
		attributeVec_t _attributes;

		GLTFPrimitive* _pPrimitive;

		std::vector<draco::DataBuffer*> buffers;
		draco::Mesh* _pMesh;
	};
}

#endif // _FLOWLIBS_GLTF_DRACOEXTENSION_H
