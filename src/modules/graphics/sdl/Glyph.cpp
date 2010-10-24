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

#include "Glyph.h"

// STD
#include <cstring> // For memcpy
#include <cstdio>

namespace love
{
namespace graphics
{
namespace sdl
{

	Glyph::Glyph(love::font::GlyphData * data, SDL_Surface *screen)
		: data(data), width((float)data->getWidth()), height((float)data->getHeight()), screen(screen)
	{
		data->retain();
	}

	Glyph::~Glyph()
	{
		if(data != 0)
			data->release();
		unload();
	}

	void Glyph::draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const
	{
		if (screen == 0 || surface == 0)
			return;
		SDL_Rect destrect;
		destrect.x = x-ox;
		destrect.y = y-oy;
		if (angle != 0 || sx != 1 || sy != 1)
		{
			SDL_Surface *rotozoomed = rotozoomSurfaceXY(surface, LOVE_TODEG(angle), sx, sy, SMOOTHING_OFF);
			SDL_BlitSurface(rotozoomed, 0, screen, &destrect);
			SDL_FreeSurface(rotozoomed);
		}
		else
			SDL_BlitSurface(surface, 0, screen, &destrect);
	}

	bool Glyph::load()
	{
		return loadVolatile();
	}

	void Glyph::unload()
	{
		unloadVolatile();
	}

	bool Glyph::loadVolatile()
	{
		if (surface != 0)
			return true;
		width = data->getWidth();
		height = data->getHeight();
		surface = SDL_CreateRGBSurface(SDL_SRCALPHA | SDL_SWSURFACE, width, height, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
		SDL_LockSurface(surface);
		if (data->getFormat() == love::font::GlyphData::FORMAT_LUMINOSITY_ALPHA)
		{
			uint16_t *imgdata = (uint16_t*) data->getData();
			uint32_t *surfdata = (uint32_t*) surface->pixels;
			int x = 0;
			int y = 0;
			int w = width;
			int h = height;
			for (; y < h; x++)
			{
				if (x == w)
				{
					++y;
					x = 0;
				}
				uint8_t lum = (imgdata[y*w+x] & 0xFF00) >> 8;
				uint8_t alpha = (imgdata[y*w+x+1] & 0x00FF);
				surfdata[y*w+x] = (lum << 24) | (lum << 16) | (lum << 8) | alpha;
			}
		}
		else
			memcpy(surface->pixels, data->getData(), data->getSize());
		SDL_UnlockSurface(surface);
		return (surface != 0);
	}

	void Glyph::unloadVolatile()
	{
		SDL_FreeSurface(surface);
		surface = 0;
	}

	float Glyph::getWidth() const
	{
		return width;
	}

	float Glyph::getHeight() const
	{
		return height;
	}

} // sdl
} // graphics
} // love
