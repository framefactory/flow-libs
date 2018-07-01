/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_SCENE_H
#define _FLOWLIBS_GLTF_SCENE_H

#include "GLTFElement.h"

#include <vector>
#include <string>


namespace flow
{
	class GLTFNode;

	class GLTFScene : public GLTFElement
	{
		friend class GLTFAsset;

	protected:
		GLTFScene(size_t index, const std::string& name = "");
		virtual ~GLTFScene();

	public:
		void setName(const std::string& name);
		void addNode(const GLTFNode* pNode);

		virtual json toJSON() const;

	private:
		std::string _name;

		typedef std::vector<const GLTFNode*> nodeVec_t;
		nodeVec_t _nodes;
	};
}

#endif // _FLOWLIBS_GLTF_SCENE_H
