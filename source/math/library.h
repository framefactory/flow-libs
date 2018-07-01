#ifndef _FLOWLIBS_MATH_LIBRARY_H
#define _FLOWLIBS_MATH_LIBRARY_H

#include "../core/setup.h"

#if defined(WIN32)
#define F_DECLARE_EXPORT __declspec(dllexport)
#define F_DECLARE_IMPORT __declspec(dllimport)
#else
#define F_DECLARE_EXPORT
#define F_DECLARE_IMPORT
#endif

#ifndef F_MATH_SHARED
#  define F_MATH_EXPORT
#elif defined(F_MATH_LIB)
#  define F_MATH_EXPORT F_DECLARE_EXPORT
#else
#  define F_MATH_EXPORT F_DECLARE_IMPORT
#endif

#endif // _FLOWLIBS_MATH_LIBRARY_H
