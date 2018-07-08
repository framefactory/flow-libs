/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_OBJECT_H
#define _FLOWLIBS_GLTF_OBJECT_H

#include "library.h"
#include "GLTFElement.h"
#include "GLTFConstants.h"
#include "GLTFAssetInfo.h"
#include "GLTFAccessorT.h"
#include "GLTFExtension.h"

#include "../core/json.h"

#include <vector>
#include <string>


namespace flow
{
	class GLTFScene;
	class GLTFNode;
	class GLTFMeshNode;
	class GLTFSkinNode;
	class GLTFCameraNode;
	class GLTFCamera;
	class GLTFMesh;
	class GLTFBuffer;
	class GLTFBufferView;
	class GLTFMaterial;
	class GLTFTexture;
	class GLTFImage;
	class GLTFSampler;
	class GLTFSkin;
	class GLTFAnimation;

	class F_GLTF_EXPORT GLTFAsset : public GLTFElement
	{
		friend class GLTFBuffer;

	public:
		// Types
		typedef std::vector<std::string> stringVec_t;
		typedef std::vector<const GLTFExtension*> extensionVec_t;
		typedef std::vector<const GLTFScene*> sceneVec_t;
		typedef std::vector<const GLTFNode*> nodeVec_t;
		typedef std::vector<const GLTFMesh*> meshVec_t;
		typedef std::vector<const GLTFSkin*> skinVec_t;
		typedef std::vector<const GLTFCamera*> cameraVec_t;

		typedef std::vector<const GLTFBuffer*> bufferVec_t;
		typedef std::vector<const GLTFBufferView*> bufferViewVec_t;
		typedef std::vector<const GLTFAccessor*> accessorVec_t;

		typedef std::vector<const GLTFMaterial*> materialVec_t;
		typedef std::vector<const GLTFTexture*> textureVec_t;
		typedef std::vector<const GLTFImage*> imageVec_t;
		typedef std::vector<const GLTFSampler*> samplerVec_t;

		typedef std::vector<const GLTFAnimation*> animationVec_t;

		GLTFAsset();
		virtual ~GLTFAsset();

		bool saveGLTF(const std::string& gltfFilePath, int indent = -1);
		bool saveGLB(const std::string& glbFilePath);

		void setMainScene(const GLTFScene* pScene);
		void setVersion(GLTFVersion version, GLTFVersion minVersion = GLTFVersion::UNDEFINED);
		void setGenerator(const std::string& generator);
		void setCopyright(const std::string& copyright);

		void addExtension(const GLTFExtension* pExtension, bool isRequired);

		GLTFScene* createScene(const std::string& name = std::string{});

		GLTFNode* createNode(const std::string& name = "");
		GLTFMeshNode* createMeshNode(const GLTFMesh* pMesh, const std::string& name = std::string{});
		GLTFSkinNode* createSkinNode(const GLTFSkin* pSkin, const std::string& name = std::string{});
		GLTFCameraNode* createCameraNode(const GLTFCamera* pCamera, const std::string& name = std::string{});

		GLTFMesh* createMesh(const std::string& name = std::string{});
		GLTFSkin* createSkin(const std::string& name = std::string{});
		GLTFCamera* createCamera(const std::string& name = std::string{});

		GLTFBuffer* createBuffer(const std::string& name = std::string{});
		
		template<typename T>
		GLTFAccessorT<T>* createAccessor(GLTFAccessorType type, std::string& name = std::string{});

		GLTFMaterial* createMaterial(const std::string& name = std::string{});

		GLTFTexture* createTexture(const GLTFImage* pImage, const GLTFSampler* pSampler = nullptr);
		GLTFTexture* createTexture(const std::string& imageUri, const GLTFSampler* pSampler = nullptr);
		GLTFTexture* createTexture(GLTFBuffer* pBuffer, const std::string& imageFilePath, const GLTFSampler* pSampler = nullptr);
		GLTFTexture* createTexture(const GLTFBufferView* pBufferView, GLTFMimeType mimeType, const GLTFSampler* pSampler = nullptr);

		GLTFImage* createImage(const std::string& imageUri);
		GLTFImage* createImage(const GLTFBufferView* pBufferView, GLTFMimeType mimeType);

		GLTFSampler* createSampler();
		GLTFAnimation* createAnimation();

		const bufferVec_t& buffers() const { return _buffers; }

		virtual json toJSON() const;
		virtual std::string toString(int indent = -1) const;

	private:
		GLTFBufferView* _createBufferView(const std::string& name = std::string{});

		template<typename T>
		void _insertElements(json& jsonObj, const std::string& propName, const std::vector<T*>& vector) const;

		template<typename T>
		void _deleteVectorOfPointers(std::vector<T*>& vector);

		GLTFAssetInfo _asset;

		const GLTFScene* _pMainScene;

		extensionVec_t _extensionsUsed;
		stringVec_t _extensionsRequired;

		sceneVec_t _scenes;
		nodeVec_t _nodes;

		meshVec_t _meshes;
		skinVec_t _skins;
		cameraVec_t _cameras;

		bufferVec_t _buffers;
		bufferViewVec_t _bufferViews;
		accessorVec_t _accessors;

		materialVec_t _materials;
		textureVec_t _textures;
		imageVec_t _images;
		samplerVec_t _samplers;

		animationVec_t _animations;
	};

	template<typename T>
	GLTFAccessorT<T>* GLTFAsset::createAccessor(GLTFAccessorType type, std::string& name)
	{
		auto pAccessor = new GLTFAccessorT<T>(_accessors.size(), type, name);
		_accessors.push_back(pAccessor);
		return pAccessor;
	}
}

#endif // _FLOWLIBS_GLTF_OBJECT_H
