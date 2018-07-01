/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_NODE_H
#define _FLOWLIBS_GLTF_NODE_H

#include "GLTFElement.h"

#include "math/Vector3T.h"
#include "math/QuaternionT.h"
#include "math/Matrix4T.h"

#include <vector>
#include <string>


namespace flow
{
	class GLTFMesh;
	class GLTFSkin;
	class GLTFCamera;

	class GLTFNode : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFNode(size_t index, const std::string& name = "");
		virtual ~GLTFNode();

	public:
		void setName(const std::string& name);
		void addChild(const GLTFNode* pNode);

		void setMatrix(const Matrix4f& matrix);
		void setTranslation(const Vector3f& translation);
		void setRotation(const Quaternion4f& rotation);
		void setScale(const Vector3f& scale);
		void setTRS(const Vector3f& translation, const Quaternion4f& rotation, const Vector3f& scale);

		virtual json toJSON() const;

	private:
		std::string _name;

		Matrix4f* _pMatrix;
		Vector3f* _pTranslation;
		Quaternion4f* _pRotation;
		Vector3f* _pScale;

		typedef std::vector<const GLTFNode*> nodeVec_t;
		nodeVec_t _children;
	};

	class GLTFMeshNode : public GLTFNode
	{
		friend class GLTFAsset;

	protected:
		GLTFMeshNode(size_t index, const GLTFMesh* pMesh, const std::string& name = "");
		virtual ~GLTFMeshNode() { }

		virtual json toJSON() const;

	private:
		const GLTFMesh* _pMesh;
	};

	class GLTFCameraNode : public GLTFNode
	{
		friend class GLTFAsset;

	protected:
		GLTFCameraNode(size_t index, const GLTFCamera* pCamera, const std::string& name = "");
		virtual ~GLTFCameraNode() { }

		virtual json toJSON() const;

	private:
		const GLTFCamera* _pCamera;
	};

	class GLTFSkinNode : public GLTFNode
	{
		friend class GLTFAsset;

	protected:
		GLTFSkinNode(size_t index, const GLTFSkin* pSkin, const std::string& name = "");
		virtual ~GLTFSkinNode() { }

		virtual json toJSON() const;

	private:
		const GLTFSkin* _pSkin;
	};
}

#endif // _FLOWLIBS_GLTF_NODE_H
