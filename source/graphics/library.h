#ifndef _FLOWLIBS_GRAPHICS_LIBRARY_H
#define _FLOWLIBS_GRAPHICS_LIBRARY_H

#include "../core/setup.h"

#if defined(WIN32)
#define F_DECLARE_EXPORT __declspec(dllexport)
#define F_DECLARE_IMPORT __declspec(dllimport)
#else
#define F_DECLARE_EXPORT
#define F_DECLARE_IMPORT
#endif

#ifndef F_GRAPHICS_SHARED
#  define F_GRAPHICS_EXPORT
#elif defined(F_GRAPHICS_LIB)
#  define F_GRAPHICS_EXPORT F_DECLARE_EXPORT
#else
#  define F_GRAPHICS_EXPORT F_DECLARE_IMPORT
#endif

#endif // _FLOWLIBS_GRAPHICS_LIBRARY_H
