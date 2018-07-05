/**
* Flow Libs - Core
*
* @author Ralph Wiedemeier <ralph@framefactory.io>
* @copyright (c) 2018 Frame Factory GmbH.
*/

#ifndef _FLOWLIBS_CORE_LIBRARY_H
#define _FLOWLIBS_CORE_LIBRARY_H

#include "../core/setup.h"

#if defined(WIN32)
#define F_DECLARE_EXPORT __declspec(dllexport)
#define F_DECLARE_IMPORT __declspec(dllimport)
#else
#define F_DECLARE_EXPORT
#define F_DECLARE_IMPORT
#endif

#ifndef F_CORE_SHARED
#  define F_CORE_EXPORT
#elif defined(F_CORE_LIB)
#  define F_CORE_EXPORT F_DECLARE_EXPORT
#else
#  define F_CORE_EXPORT F_DECLARE_IMPORT
#endif

#endif // _FLOWLIBS_CORE_LIBRARY_H
