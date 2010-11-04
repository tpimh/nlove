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

#ifndef LOVE_GRAPHICS_SDL_GRAPHICS_H
#define LOVE_GRAPHICS_SDL_GRAPHICS_H

// General
#include <iostream>

// SDL
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

// LOVE
#include <common/config.h>
#include <graphics/Graphics.h>
#include <image/ImageData.h>
#include "Image.h"
#include "Font.h"

namespace love
{
namespace graphics
{
namespace sdl
{
	class Graphics : public love::graphics::Graphics
	{
	private:
		struct
		{
			uint8_t r, g, b, a;
		} color, backgroundColor;
		struct
		{
			int w, h;
		} currentMode;
		SDL_Surface * surface;
		Font * currentFont;

	public:
		Graphics();
		virtual ~Graphics();
		const char * getName() const;
		bool checkMode(int width, int height, bool fullscreen);
		bool setMode(int width, int height, bool fullscreen, bool vsync, int fsaa);
		int getModes(lua_State * L);
		SDL_Surface * getSurface();
		void present();
		void clear();
		void setColor(int r, int g, int b, int a);
		void setBackgroundColor(int r, int g, int b);
		bool isCreated();
		void rectangle(DrawMode mode, int x, int y, int width, int height);
		void circle(DrawMode mode, int x, int y, int radius, int segments);
		void line(float x1, float y1, float x2, float y2);
		int polyline(lua_State * L);
		void point(float x, float y);
		void triangle(DrawMode mode, float x1, float y1, float x2, float y2, float x3, float y3);
		int polygon(lua_State * L);
		void setCaption(const char * caption);
		int getCaption(lua_State * L);
		int getWidth();
		int getHeight();
		void setFont(Font * font);
		Font *getFont();
		void print(const char * str, float x, float y);
		void print(const char * str, float x, float y , float angle);
		void print(const char * str, float x, float y , float angle, float s);
		void print(const char * str, float x, float y , float angle, float sx, float sy);
		void printf(const char * str, float x, float y, float wrap, AlignMode align);

		Image * newImage(love::image::ImageData *imagedata);
		Quad * newQuad(int x, int y, int w, int h, int sw, int sh);
		Font * newFont(love::font::FontData * data);
	};
}
}
}

#endif //LOVE_GRAPHICS_SDL_GRAPHICS_H
