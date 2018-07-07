/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_NODE_H
#define _FLOWLIBS_GLTF_NODE_H

#include "library.h"
#include "GLTFMainElement.h"

#include "math/Vector3T.h"
#include "math/QuaternionT.h"
#include "math/Matrix4T.h"

#include <string>
#include <vector>


namespace flow
{
	class GLTFMesh;
	class GLTFSkin;
	class GLTFCamera;

	class F_GLTF_EXPORT GLTFNode : public GLTFMainElement
	{
		friend class GLTFAsset;

	protected:
		GLTFNode(size_t index, const std::string& name = std::string{});
		virtual ~GLTFNode();

	public:
		typedef std::vector<const GLTFNode*> nodeVec_t;

		void addChild(const GLTFNode* pNode);
		void setMatrix(const Matrix4f& matrix);
		void setTranslation(const Vector3f& translation);
		void setRotation(const Quaternion4f& rotation);
		void setScale(const Vector3f& scale);
		void setTRS(const Vector3f& translation, const Quaternion4f& rotation, const Vector3f& scale);

		const nodeVec_t& children() const { return _children; }
		const Matrix4f* matrix() const { return _pMatrix; }
		const Vector3f* translation() const { return _pTranslation; }
		const Quaternion4f* rotation() const { return _pRotation; }
		const Vector3f* scale() const { return _pScale; }

		virtual json toJSON() const;

	private:
		nodeVec_t _children;
		Matrix4f* _pMatrix;
		Vector3f* _pTranslation;
		Quaternion4f* _pRotation;
		Vector3f* _pScale;
	};

	class F_GLTF_EXPORT GLTFMeshNode : public GLTFNode
	{
		friend class GLTFAsset;

	protected:
		GLTFMeshNode(size_t index, const GLTFMesh* pMesh, const std::string& name = std::string{});
		virtual ~GLTFMeshNode() { }

		virtual json toJSON() const;

	private:
		const GLTFMesh* _pMesh;
	};

	class F_GLTF_EXPORT GLTFCameraNode : public GLTFNode
	{
		friend class GLTFAsset;

	protected:
		GLTFCameraNode(size_t index, const GLTFCamera* pCamera, const std::string& name = std::string{});
		virtual ~GLTFCameraNode() { }

		virtual json toJSON() const;

	private:
		const GLTFCamera* _pCamera;
	};

	class F_GLTF_EXPORT GLTFSkinNode : public GLTFNode
	{
		friend class GLTFAsset;

	protected:
		GLTFSkinNode(size_t index, const GLTFSkin* pSkin, const std::string& name = std::string{});
		virtual ~GLTFSkinNode() { }

		virtual json toJSON() const;

	private:
		const GLTFSkin* _pSkin;
	};
}

#endif // _FLOWLIBS_GLTF_NODE_H
