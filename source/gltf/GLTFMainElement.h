/**
* Flow Libs - GLTF
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_GLTF_MAINELEMENT_H
#define _FLOWLIBS_GLTF_MAINELEMENT_H

#include "library.h"
#include "GLTFElement.h"

#include <string>

namespace flow
{
	class F_GLTF_EXPORT GLTFMainElement : public GLTFElement
	{
	protected:
		GLTFMainElement(size_t index, const std::string& name = std::string{});
		virtual ~GLTFMainElement() { };

	public:
		void setName(const std::string& name);

		const std::string& name() const { return _name; }
		size_t index() const { return _index; }

		virtual json toJSON() const;

	private:
		size_t _index;
		std::string _name;
	};
}

#endif // _FLOWLIBS_GLTF_MAINELEMENT_H
