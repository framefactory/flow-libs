/**
* Flow Libs - Core
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_CORE_DEBUGSTREAM_H
#define _FLOWLIBS_CORE_DEBUGSTREAM_H

#include "library.h"
#include <sstream>

namespace flow
{
	class F_CORE_EXPORT DebugStream : public std::stringbuf
	{
	public:
		static void start();

	protected:
		DebugStream();
		virtual ~DebugStream();

		int sync();

		struct Guard
		{
			Guard() : pInstance(nullptr) { }
			~Guard() { F_SAFE_DELETE(pInstance); }

			DebugStream* pInstance;
		};

		static Guard s_guard;
	};
}

#endif // _FLOWLIBS_CORE_DEBUGSTREAM_H