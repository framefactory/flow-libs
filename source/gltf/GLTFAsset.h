/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_ASSET_H
#define _FLOWLIBS_GLTF_ASSET_H

#include "library.h"

#include "GLTFElement.h"
#include "GLTFImage.h"

#include "../core/json.h"

#include <vector>
#include <string>


namespace flow
{
	class GLTFElement;
	class GLTFScene;
	class GLTFNode;
	class GLTFMeshNode;
	class GLTFSkinNode;
	class GLTFCameraNode;
	class GLTFCamera;
	class GLTFMesh;
	class GLTFBuffer;
	class GLTFBufferView;
	class GLTFAccessor;
	class GLTFMaterial;
	class GLTFTexture;
	class GLTFImage;
	class GLTFSampler;
	class GLTFSkin;
	class GLTFAnimation;

	enum class GLTFVersion
	{
		GLTF_1_0,
		GLTF_2_0
	};

	class F_GLTF_EXPORT GLTFAsset : public GLTFElement
	{
	public:
		// Types
		typedef std::vector<GLTFScene*> sceneVec_t;
		typedef std::vector<GLTFNode*> nodeVec_t;
		typedef std::vector<GLTFMesh*> meshVec_t;
		typedef std::vector<GLTFSkin*> skinVec_t;
		typedef std::vector<GLTFCamera*> cameraVec_t;

		typedef std::vector<GLTFBuffer*> bufferVec_t;
		typedef std::vector<GLTFBufferView*> bufferViewVec_t;
		typedef std::vector<GLTFAccessor*> accessorVec_t;

		typedef std::vector<GLTFMaterial*> materialVec_t;
		typedef std::vector<GLTFTexture*> textureVec_t;
		typedef std::vector<GLTFImage*> imageVec_t;
		typedef std::vector<GLTFSampler*> samplerVec_t;

		typedef std::vector<GLTFAnimation*> animationVec_t;

		GLTFAsset();
		virtual ~GLTFAsset();

		void setMainScene(const GLTFScene* pScene);
		void setVersion(GLTFVersion version);
		void setGenerator(const std::string& generator);
		void setCopyright(const std::string& copyright);

		GLTFScene* createScene(const std::string& name = std::string{});

		GLTFNode* createNode(const std::string& name = "");
		GLTFMeshNode* createMeshNode(const GLTFMesh* pMesh, const std::string& name = std::string{});
		GLTFSkinNode* createSkinNode(const GLTFSkin* pSkin, const std::string& name = std::string{});
		GLTFCameraNode* createCameraNode(const GLTFCamera* pCamera, const std::string& name = std::string{});

		GLTFMesh* createMesh(const std::string& name = std::string{});
		GLTFSkin* createSkin(const std::string& name = std::string{});
		GLTFCamera* createCamera(const std::string& name = std::string{});

		GLTFBuffer* createBuffer(size_t byteLength, const std::string& name = std::string{});
		GLTFBufferView* createBufferView(const GLTFBuffer* pBuffer, const std::string& name = std::string{});
		GLTFAccessor* createAccessor(const GLTFBufferView* pView, const std::string& name = std::string{});

		GLTFMaterial* createMaterial(const std::string& name = std::string{});

		GLTFTexture* createTexture(const GLTFImage* pImage, const GLTFSampler* pSampler = nullptr);
		GLTFTexture* createTexture(const std::string& imageUri, const GLTFSampler* pSampler = nullptr);
		GLTFTexture* createTexture(const GLTFBufferView* pBufferView, GLTFMimeType mimeType, const GLTFSampler* pSampler = nullptr);

		GLTFImage* createImage(const std::string& imageUri);
		GLTFImage* createImage(const GLTFBufferView* pBufferView, GLTFMimeType mimeType);

		GLTFSampler* createSampler();

		GLTFAnimation* createAnimation();

		virtual json toJSON() const;
		virtual std::string toString(int indent = -1) const;

	private:
		template<typename T>
		void _insertElements(json& jsonObj, const std::string& propName, const std::vector<T*>& vector) const;

		template<typename T>
		void _deleteVectorOfPointers(std::vector<T*>& vector);

		const char* _versionToString() const;

		GLTFVersion _version;
		std::string _generator;
		std::string _copyright;

		const GLTFScene* _pMainScene;

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
}

#endif // _FLOWLIBS_GLTF_ASSET_H
