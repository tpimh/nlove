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

#include "wrap_Graphics.h"

namespace love
{
namespace graphics
{
namespace sdl
{
	static Graphics * instance = 0;

	int w_checkMode(lua_State * L)
	{
		int w = luaL_checkint(L, 1);
		int h = luaL_checkint(L, 2);
		bool fs = luax_optboolean(L, 3, false);
		luax_pushboolean(L, instance->checkMode(w, h, fs));
		return 1;
	}

	int w_setMode(lua_State * L)
	{
		int w = luaL_checkint(L, 1);
		int h = luaL_checkint(L, 2);
		bool fs = luax_optboolean(L, 3, false);
		bool vsync = luax_optboolean(L, 4, true);
		int fsaa = luaL_optint(L, 5, 0);
		luax_pushboolean(L, instance->setMode(w, h, fs, vsync, fsaa));
		return 1;
	}

	int w_getModes(lua_State * L)
	{
		return instance->getModes(L);
	}

	int w_newImage(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_convobj(L, 1, "filesystem", "newFile");

		// Convert to ImageData, if necessary.
		if(luax_istype(L, 1, FILESYSTEM_FILE_T) || (luax_istype(L, 1, DATA_T) && !luax_istype(L, 1, IMAGE_IMAGE_DATA_T)))
			luax_convobj(L, 1, "image", "newImageData");

		love::image::ImageData * data = luax_checktype<love::image::ImageData>(L, 1, "ImageData", IMAGE_IMAGE_DATA_T);

		// Create the image.
		Image * image = 0;
		try {
			image = instance->newImage(data);
		} catch (love::Exception & e) {
			luaL_error(L, e.what());
		}

		if(image == 0)
			return luaL_error(L, "Could not load image.");


		// Push the type.
		luax_newtype(L, "Image", GRAPHICS_IMAGE_T, (void*)image);

		return 1;
	}

	int w_draw(lua_State * L)
	{
		Drawable * drawable = luax_checktype<Drawable>(L, 1, "Drawable", GRAPHICS_DRAWABLE_T);
		float x = (float)luaL_optnumber(L, 2, 0.0f);
		float y = (float)luaL_optnumber(L, 3, 0.0f);
		float angle = (float)luaL_optnumber(L, 4, 0.0f);
		float sx = (float)luaL_optnumber(L, 5, 1.0f);
		float sy = (float)luaL_optnumber(L, 6, sx);
		float ox = (float)luaL_optnumber(L, 7, 0);
		float oy = (float)luaL_optnumber(L, 8, 0);
		drawable->draw(x, y, angle, sx, sy, ox, oy);
		return 0;
	}

	int w_present(lua_State * L)
	{
		instance->present();
		return 0;
	}

	int w_clear(lua_State * L)
	{
		instance->clear();
		return 0;
	}

	int w_setColor(lua_State * L)
	{
		int r, g, b, a;
		if (lua_istable(L, 1)) {
			lua_pushinteger(L, 1);
			lua_gettable(L, -2);
			r = (unsigned char)luaL_checkint(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 2);
			lua_gettable(L, -2);
			g = (unsigned char)luaL_checkint(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 3);
			lua_gettable(L, -2);
			b = (unsigned char)luaL_checkint(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 4);
			lua_gettable(L, -2);
			a = (unsigned char)luaL_optint(L, -1, 255);
			lua_pop(L, 1);
		}
		else
		{
			r = (unsigned char)luaL_checkint(L, 1);
			g = (unsigned char)luaL_checkint(L, 2);
			b = (unsigned char)luaL_checkint(L, 3);
			a = (unsigned char)luaL_optint(L, 4, 255);
		}
		instance->setColor(r, g, b, a);
		return 0;
	}

	int w_setBackgroundColor(lua_State * L)
	{
		int r, g, b;
		if (lua_istable(L, 1)) {
			lua_pushinteger(L, 1);
			lua_gettable(L, -2);
			r = (unsigned char)luaL_checkint(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 2);
			lua_gettable(L, -2);
			g = (unsigned char)luaL_checkint(L, -1);
			lua_pop(L, 1);
			lua_pushinteger(L, 3);
			lua_gettable(L, -2);
			b = (unsigned char)luaL_checkint(L, -1);
			lua_pop(L, 1);
		}
		else
		{
			r = (unsigned char)luaL_checkint(L, 1);
			g = (unsigned char)luaL_checkint(L, 2);
			b = (unsigned char)luaL_checkint(L, 3);
		}
		instance->setBackgroundColor(r, g, b);
		return 0;
	}

	int w_rectangle(lua_State * L)
	{
		Graphics::DrawMode mode;
		const char * str = luaL_checkstring(L, 1);
		if(!Graphics::getConstant(str, mode))
			return luaL_error(L, "Incorrect draw mode %s", str);

		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float w = (float)luaL_checknumber(L, 4);
		float h = (float)luaL_checknumber(L, 5);
		instance->rectangle(mode, x, y, w, h);
		return 0;
	}

	int w_circle(lua_State * L)
	{
		Graphics::DrawMode mode;
		const char * str = luaL_checkstring(L, 1);
		if(!Graphics::getConstant(str, mode))
			return luaL_error(L, "Incorrect draw mode %s", str);

		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float r = (float)luaL_checknumber(L, 4);
		float s = (float)luaL_checknumber(L, 5);
		instance->circle(mode, x, y, r, s);
		return 0;
	}

	int w_line(lua_State * L)
	{
		int args = lua_gettop(L);
		if( args == 1 || args > 4) {
			instance->polyline(L);
		} else {
			float x1 = (float)luaL_checknumber(L, 1);
			float y1 = (float)luaL_checknumber(L, 2);
			float x2 = (float)luaL_checknumber(L, 3);
			float y2 = (float)luaL_checknumber(L, 4);
			instance->line(x1, y1, x2, y2);
		}
		return 0;
	}

	int w_point(lua_State * L)
	{
		float x = (float)luaL_checknumber(L, 1);
		float y = (float)luaL_checknumber(L, 2);
		instance->point(x, y);
		return 0;
	}

	int w_triangle(lua_State * L)
	{
		Graphics::DrawMode mode;
		const char * str = luaL_checkstring(L, 1);
		if(!Graphics::getConstant(str, mode))
			return luaL_error(L, "Incorrect draw mode %s", str);

		float x1 = (float)luaL_checknumber(L, 2);
		float y1 = (float)luaL_checknumber(L, 3);
		float x2 = (float)luaL_checknumber(L, 4);
		float y2 = (float)luaL_checknumber(L, 5);
		float x3 = (float)luaL_checknumber(L, 6);
		float y3 = (float)luaL_checknumber(L, 7);
		instance->triangle(mode, x1, y1, x2, y2, x3, y3);
		return 0;
	}

	int w_polygon(lua_State * L)
	{
		return instance->polygon(L);
	}

	int w_setCaption(lua_State * L)
	{
		instance->setCaption(luaL_checkstring(L, 1));
		return 0;
	}

	int w_getCaption(lua_State * L)
	{
		return instance->getCaption(L);
	}

	int w_getWidth(lua_State * L)
	{
		lua_pushnumber(L, instance->getWidth());
		return 1;
	}

	int w_getHeight(lua_State * L)
	{
		lua_pushnumber(L, instance->getHeight());
		return 1;
	}

	int w_isCreated(lua_State * L)
	{
		lua_pushboolean(L, instance->isCreated());
		return 1;
	}

	int w_newQuad(lua_State * L)
	{
		int x = luaL_checkint(L, 1);
		int y = luaL_checkint(L, 2);
		int w = luaL_checkint(L, 3);
		int h = luaL_checkint(L, 4);
		int sw = luaL_checkint(L, 5);
		int sh = luaL_checkint(L, 6);

		Quad * frame = instance->newQuad(x, y, w, h, sw, sh);

		if (frame == 0)
			return luaL_error(L, "Could not create frame.");

		luax_newtype(L, "Quad", GRAPHICS_QUAD_T, (void*)frame);
		return 1;
	}

	int w_newFont1(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_convobj(L, 1, "filesystem", "newFile");

		// Convert to Data, if necessary.
		if(luax_istype(L, 1, FILESYSTEM_FILE_T)) {
			love::filesystem::File * f = luax_checktype<love::filesystem::File>(L, 1, "File", FILESYSTEM_FILE_T);
			Data * d;
			try {
				d = f->read();
			}
			catch (love::Exception & e) {
				return luaL_error(L, e.what());
			}
			lua_remove(L, 1); // get rid of the file
			luax_newtype(L, "Data", DATA_T, (void*)d);
			lua_insert(L, 1); // put it at the bottom of the stack
		}

		// Convert to Rasterizer, if necessary.
		if(luax_istype(L, 1, DATA_T) && !luax_istype(L, 1, FONT_FONT_DATA_T)) {
			int idxs[] = {1, 2};
			luax_convobj(L, idxs, 2, "font", "newRasterizer");
		}

		// Convert to FontData, if necessary.
		if(luax_istype(L, 1, FONT_RASTERIZER_T))
			luax_convobj(L, 1, "font", "newFontData");

		love::font::FontData * data = luax_checktype<love::font::FontData>(L, 1, "FontData", FONT_FONT_DATA_T);

		// Create the font.
		Font * font = instance->newFont(data);

		if(font == 0)
			return luaL_error(L, "Could not load font.");

		// Push the type.
		luax_newtype(L, "Font", GRAPHICS_FONT_T, (void*)font);

		return 1;
	}

	int w_newImageFont(lua_State * L)
	{
		// Convert to ImageData if necessary.
		if(lua_isstring(L, 1) || luax_istype(L, 1, FILESYSTEM_FILE_T) || luax_istype(L, 1, DATA_T))
			luax_convobj(L, 1, "image", "newImageData");

		// Convert to Rasterizer if necessary.
		if(luax_istype(L, 1, IMAGE_IMAGE_DATA_T)) {
			int idxs[] = {1, 2};
			luax_convobj(L, idxs, 2, "font", "newRasterizer");
		}

		// Convert to FontData, if necessary.
		if(luax_istype(L, 1, FONT_RASTERIZER_T))
			luax_convobj(L, 1, "font", "newFontData");

		love::font::FontData * data = luax_checktype<love::font::FontData>(L, 1, "FontData", FONT_FONT_DATA_T);

		// Create the font.
		Font * font = instance->newFont(data);

		if(font == 0)
			return luaL_error(L, "Could not load font.");

		// Push the type.
		luax_newtype(L, "Font", GRAPHICS_FONT_T, (void*)font);

		return 1;
	}

	int w_setFont1(lua_State * L)
	{
		// The second parameter is an optional int.
		int size = luaL_optint(L, 2, 12);

		Font * font;

		// If the first parameter isn't a Font, create a new one
		if (!luax_istype(L, 1, GRAPHICS_FONT_T)) {
			lua_pushinteger(L, size); // push the size
			lua_insert(L, 2); // move it to its proper place
			// Convert to File, if necessary.
			if(lua_isstring(L, 1))
				luax_convobj(L, 1, "filesystem", "newFile");

			// Convert to Data, if necessary.
			if(luax_istype(L, 1, FILESYSTEM_FILE_T)) {
				love::filesystem::File * f = luax_checktype<love::filesystem::File>(L, 1, "File", FILESYSTEM_FILE_T);
				Data * d = f->read();
				lua_remove(L, 1); // get rid of the file
				luax_newtype(L, "Data", DATA_T, (void*)d);
				lua_insert(L, 1); // put it at the bottom of the stack
			}

			// Convert to Rasterizer, if necessary.
			if(luax_istype(L, 1, DATA_T) && !luax_istype(L, 1, FONT_FONT_DATA_T)) {
				int idxs[] = {1, 2};
				luax_convobj(L, idxs, 2, "font", "newRasterizer");
			}

			// Convert to FontData, if necessary.
			if(luax_istype(L, 1, FONT_RASTERIZER_T))
				luax_convobj(L, 1, "font", "newFontData");

			love::font::FontData * data = luax_checktype<love::font::FontData>(L, 1, "FontData", FONT_FONT_DATA_T);

			// Create the font.
			font = instance->newFont(data);

			if(font == 0)
				return luaL_error(L, "Could not load font.");
		}
		else font = luax_checktype<Font>(L, 1, "Font", GRAPHICS_FONT_T);
		instance->setFont(font);
		return 0;
	}

	int w_getFont(lua_State * L)
	{
		Font * f = instance->getFont();

		if(f == 0)
			return 0;

		f->retain();
		luax_newtype(L, "Font", GRAPHICS_FONT_T, (void*)f);
		return 1;
	}

	int w_drawq(lua_State * L)
	{
		Image * image = luax_checktype<Image>(L, 1, "Image", GRAPHICS_IMAGE_T);
		Quad * q = luax_checkframe(L, 2);
		float x = (float)luaL_checknumber(L, 3);
		float y = (float)luaL_checknumber(L, 4);
		float angle = (float)luaL_optnumber(L, 5, 0);
		float sx = (float)luaL_optnumber(L, 6, 1);
		float sy = (float)luaL_optnumber(L, 7, sx);
		float ox = (float)luaL_optnumber(L, 8, 0);
		float oy = (float)luaL_optnumber(L, 9, 0);
		image->drawq(q, x, y, angle, sx, sy, ox, oy);
		return 0;
	}

	int w_print1(lua_State * L)
	{
		const char * str = luaL_checkstring(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float angle = (float)luaL_optnumber(L, 4, 0.0f);
		float sx = (float)luaL_optnumber(L, 5, 1.0f);
		float sy = (float)luaL_optnumber(L, 6, sx);

		switch(lua_gettop(L))
		{
		case 3:
			instance->print(str, x, y);
			break;
		case 4:
			instance->print(str, x, y, angle);
			break;
		case 5:
			instance->print(str, x, y, angle, sx);
			break;
		case 6:
			instance->print(str, x, y, angle, sx, sy);
			break;
		default:
			return luaL_error(L, "Incorrect number of parameters");
		}
		return 0;
	}

	int w_printf1(lua_State * L)
	{
		const char * str = luaL_checkstring(L, 1);
		float x = (float)luaL_checknumber(L, 2);
		float y = (float)luaL_checknumber(L, 3);
		float wrap = (float)luaL_checknumber(L, 4);

		Graphics::AlignMode align = Graphics::ALIGN_LEFT;

		if(lua_gettop(L) >= 5)
		{
			const char * str = luaL_checkstring(L, 5);
			if(!Graphics::getConstant(str, align))
				return luaL_error(L, "Incorrect alignment: %s", str);
		}

		instance->printf(str, x, y, wrap, align);
		return 0;
	}

	// List of functions to wrap.
	static const luaL_Reg functions[] = {
		{ "checkMode", w_checkMode },
		{ "setMode", w_setMode },
		{ "getModes", w_getModes },
		{ "newImage", w_newImage },
		{ "draw", w_draw },
		{ "present", w_present },
		{ "clear", w_clear },
		{ "setBackgroundColor", w_setBackgroundColor },
		{ "setColor", w_setColor },
		{ "rectangle", w_rectangle },
		{ "circle", w_circle },
		{ "line", w_line },
		{ "point", w_point },
		{ "triangle", w_triangle },
		{ "polygon", w_polygon },
		{ "setCaption", w_setCaption },
		{ "getCaption", w_getCaption },
		{ "getWidth", w_getWidth },
		{ "getHeight", w_getHeight },
		{ "isCreated", w_isCreated },
		{ "newQuad", w_newQuad },
		{ "drawq", w_drawq },
		{ "setFont1", w_setFont1 },
		{ "getFont", w_getFont },
		{ "newFont1", w_newFont1 },
		{ "newImageFont", w_newImageFont },
		{ "print1", w_print1 },
		{ "printf1", w_printf1 },
		{ 0, 0 }
	};

	// Types for this module.
	static const lua_CFunction types[] = {
		luaopen_image,
		luaopen_frame,
		luaopen_font,
		0
	};

	int luaopen_love_graphics(lua_State * L)
	{
		if(instance == 0)
		{
			try
			{
				instance = new Graphics();
			}
			catch(Exception & e)
			{
				return luaL_error(L, e.what());
			}
		}
		else
			instance->retain();

		WrappedModule w;
		w.module = instance;
		w.name = "graphics";
		w.flags = MODULE_T;
		w.functions = functions;
		w.types = types;

		luax_register_module(L, w);

		if (luaL_loadbuffer(L, (const char *)graphics_lua, sizeof(graphics_lua), "graphics.lua") == 0)
			lua_call(L, 0, 0);

		return 0;
	}

} // sdl
} // graphics
} // love
