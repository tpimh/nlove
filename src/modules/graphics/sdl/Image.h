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

#ifndef LOVE_GRAPHICS_SDL_IMAGE_H
#define LOVE_GRAPHICS_SDL_IMAGE_H

// LOVE
#include <common/config.h>
#include <common/Data.h>
#include <common/math.h>
#include <graphics/Image.h>
#include "Quad.h"
#include <filesystem/File.h>
#include <image/Image.h>

// SDL
#include <SDL_image.h>
#include <SDL_rotozoom.h>

namespace love
{
namespace graphics
{
namespace sdl
{
	class Image : public love::graphics::Image
	{
	private:
		struct
		{
			float angle, sx, sy;
		} rotozoom;
		love::image::ImageData *imagedata;
		SDL_RWops *rw;
		SDL_Surface *surface, *screen, *rotozoomed;
		float width, height;

	public:
		Image(love::image::ImageData *imagedata, SDL_Surface * screen = 0);
		virtual ~Image();
		void draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const;
		void drawq(Quad * quad, float x, float y, float angle, float sx, float sy, float ox, float oy) const;
		bool loadVolatile();
		void unloadVolatile();
		float getWidth();
		float getHeight();
	};
} // sdl
} // graphics
} // love

#endif // LOVE_GRAPHICS_SDL_IMAGE_H
