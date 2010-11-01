/**
* Copyright (c) 2006-2010 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
**/

#ifndef LOVE_CONFIG_H
#define LOVE_CONFIG_H

#define LOVE_LINUX 1

#cmakedefine LOVE_LITTLE_ENDIAN 1
#cmakedefine LOVE_BIG_ENDIAN 1

#ifndef LOVE_BUILD
#	define LOVE_BUILD
#	define LOVE_BUILD_STANDALONE
#	define LOVE_BUILD_EXE
//#	define LOVE_BUILD_DLL
#endif

#define LOVE_EXPORT

#cmakedefine LOVE_SCREEN_DEPTH @LOVE_SCREEN_DEPTH@

#cmakedefine LOVE_HAS_FINITE

#cmakedefine LOVE_PLATFORM @LOVE_PLATFORM@

#ifdef LOVE_HAS_FINITE
#	define b2finite(x) finite(x)
#else
#	define b2finite(x) (sizeof (x) == sizeof (float) ? __finitef (x) : __finite (x))
#endif

#endif // LOVE_CONFIG_H
