/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_SCENE_H
#define _FLOWLIBS_GLTF_SCENE_H

#include "library.h"
#include "GLTFMainElement.h"

#include <vector>
#include <string>


namespace flow
{
	class GLTFNode;

	class GLTFScene : public GLTFMainElement
	{
		friend class GLTFObject;

	protected:
		GLTFScene(size_t index, const std::string& name = std::string{});
		virtual ~GLTFScene();

	public:
		typedef std::vector<const GLTFNode*> nodeVec_t;

		void addNode(const GLTFNode* pNode);

		const nodeVec_t& nodes() const { return _nodes; }

		virtual json toJSON() const;

	private:
		nodeVec_t _nodes;
	};
}

#endif // _FLOWLIBS_GLTF_SCENE_H
