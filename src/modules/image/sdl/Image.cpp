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

#include "Image.h"

#include "ImageData.h"

// SDL
#include <SDL_image.h>

namespace love
{
namespace image
{
namespace sdl
{
	Image::Image()
	{
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	}

	Image::~Image()
	{
		IMG_Quit();
	}

	const char * Image::getName() const
	{
		return "love.image.sdl";
	}

	love::image::ImageData * Image::newImageData(love::filesystem::File * file)
	{
		return new ImageData(file);
	}

	love::image::ImageData * Image::newImageData(Data * data)
	{
		try {
			return new ImageData(data);
		} catch (love::Exception & e) {
			throw love::Exception(e.what());
		}

	}

	love::image::ImageData * Image::newImageData(int width, int height)
	{
		return new ImageData(width, height);
	}

	love::image::ImageData * Image::newImageData(int width, int height, void *data)
	{
		return new ImageData(width, height, data);
	}
} // sdl
} // image
} // love
