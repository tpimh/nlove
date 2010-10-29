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

#include "ImageData.h"

// STD
#include <iostream>

// LOVE
#include <common/Exception.h>

namespace love
{
namespace image
{
namespace sdl
{
	void ImageData::load(Data * data)
	{
		SDL_RWops *rw = SDL_RWFromConstMem(data->getData(), data->getSize());
		SDL_Surface *origimage = IMG_Load_RW(rw, 1);
		SDL_PixelFormat fmt = {
			0,
			32,
			4,
			0, 0, 0, 0,
			24, 16, 8, 0,
			0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff,
			0x000000ff,
			0x00,
		};
		image = SDL_ConvertSurface(origimage, &fmt, SDL_SRCALPHA | SDL_HWSURFACE);
		SDL_FreeSurface(origimage);
		bpp = 4;
		width = image->w;
		height = image->h;
		SDL_LockSurface(image);
	}

	ImageData::ImageData(Data * data)
	{
		load(data);
	}

	ImageData::ImageData(filesystem::File * file)
	{
		Data * data = file->read();
		load(data);
		data->release();
	}

	ImageData::ImageData(int width, int height)
		: width(width), height(height), bpp(4)
	{
		image = SDL_CreateRGBSurface(SDL_SRCALPHA | SDL_SWSURFACE, width, height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
		SDL_LockSurface(image);
	}

	ImageData::ImageData(int width, int height, void * data)
	{
	}

	ImageData::~ImageData()
	{
		SDL_FreeSurface(image);
	}

	void * ImageData::getData() const
	{
		return image->pixels;
	}

	int ImageData::getSize() const
	{
		return width*height*bpp;
	}

	int ImageData::getWidth() const
	{
		return width;
	}

	int ImageData::getHeight() const
	{
		return height;
	}

	void ImageData::setPixel(int x, int y, pixel c)
	{
		int32_t * pixeldata = (int32_t*) image->pixels;
		pixeldata[width*y+x] = (c.r << 24 | c.g << 16 | c.b << 8 | c.a);
	}

	pixel ImageData::getPixel(int x, int y) const
	{
		int32_t * pixeldata = (int32_t*) image->pixels;
		pixel c;
		c.r = (pixeldata[width*y+x] & 0xff000000) >> 24;
		c.g = (pixeldata[width*y+x] & 0x00ff0000) >> 16;
		c.b = (pixeldata[width*y+x] & 0x0000ff00) >> 8;
		c.a = (pixeldata[width*y+x] & 0x000000ff) >> 0;
		return c;
	}

	EncodedImageData * ImageData::encode(EncodedImageData::Format f)
	{
		return new EncodedImageData(0, f, 0);
	}
} // sdl
} // image
} // love
