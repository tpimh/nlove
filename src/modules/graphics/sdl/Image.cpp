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

// LOVE
#include "Image.h"

namespace love
{
namespace graphics
{
namespace sdl
{
	Image::Image(love::image::ImageData *imagedata, SDL_Surface * screen)
		: screen(screen), surface(0), imagedata(imagedata), width(0), height(0)
	{
		imagedata->retain();
		loadVolatile();
	}

	Image::~Image()
	{
		unloadVolatile();
		imagedata->release();
	}

	void Image::draw(float x, float y, float angle, float sx, float sy, float ox, float oy) const
	{
		if (screen == 0 || surface == 0)
			return;
		SDL_Rect destrect;
		destrect.x = x+(ox*sx*cos(angle)-oy*sy*sin(angle));
		destrect.y = y-(ox*sx*sin(angle)+oy*sy*cos(angle));
		if (angle != 0 || sx != 1 || sy != 1)
		{
			SDL_Surface *rotozoomed = rotozoomSurfaceXY(surface, -LOVE_TODEG(angle), sx, sy, SMOOTHING_OFF);
			destrect.x = destrect.x-(rotozoomed->w-surface->w);
			destrect.y = destrect.y-(rotozoomed->h-surface->h);
			SDL_BlitSurface(rotozoomed, 0, screen, &destrect);
			SDL_FreeSurface(rotozoomed);
		}
		else
			SDL_BlitSurface(surface, 0, screen, &destrect);
	}

	void Image::drawq(Quad * quad, float x, float y, float angle, float sx, float sy, float ox, float oy) const
	{
		if (screen == 0 || surface == 0)
			return;
		SDL_Rect srcrect, destrect;
		destrect.x = x-(ox*sx*cos(angle)-oy*sy*sin(angle));
		destrect.y = y-(ox*sx*sin(angle)+oy*sy*cos(angle));
		Quad::Viewport v = quad->getViewport();
		srcrect.x = v.x;
		srcrect.y = v.y;
		srcrect.w = v.w;
		srcrect.h = v.h;
		if (angle != 0 || sx != 1 || sy != 1)
		{
			SDL_Surface *rotozoomed = rotozoomSurfaceXY(surface, -LOVE_TODEG(angle), sx, sy, SMOOTHING_OFF);
			SDL_BlitSurface(rotozoomed, &srcrect, screen, &destrect);
			SDL_FreeSurface(rotozoomed);
		}
		else
			SDL_BlitSurface(surface, &srcrect, screen, &destrect);
	}

	bool Image::loadVolatile()
	{
		if (surface != 0)
			return true;
		width = imagedata->getWidth();
		height = imagedata->getHeight();
		surface = SDL_CreateRGBSurface(SDL_SRCALPHA | SDL_SWSURFACE, width, height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
		SDL_LockSurface(surface);
		memcpy(surface->pixels, imagedata->getData(), imagedata->getSize());
		SDL_UnlockSurface(surface);
		return (surface != 0);
	}

	void Image::unloadVolatile()
	{
		SDL_FreeSurface(surface);
		surface = 0;
	}

	float Image::getWidth()
	{
		return width;
	}

	float Image::getHeight()
	{
		return height;
	}
} // sdl
} // graphics
} // love
