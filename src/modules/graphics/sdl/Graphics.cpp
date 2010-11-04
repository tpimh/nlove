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

#include "Graphics.h"

namespace love
{
namespace graphics
{
namespace sdl
{

	Graphics::Graphics()
		: surface(0), currentFont(0)
	{
		// Window should be centered.
		SDL_putenv(const_cast<char *>("SDL_VIDEO_CENTERED=center"));

		setColor(255, 255, 255, 255);
		setBackgroundColor(0, 0, 0);

		if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
			throw Exception(SDL_GetError());
	}

	Graphics::~Graphics()
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}

	const char * Graphics::getName() const
	{
		return "love.graphics.sdl";
	}

	bool Graphics::checkMode(int width, int height, bool fullscreen)
	{
		Uint32 sdlflags = fullscreen ? SDL_FULLSCREEN : 0;

		// Check if mode is supported
		int bpp = SDL_VideoModeOK(width, height, LOVE_SCREEN_DEPTH, sdlflags);

		return (bpp >= 16);
	}

	bool Graphics::setMode(int width, int height, bool fullscreen, bool vsync, int fsaa)
	{
		// Fullscreen?
		Uint32 sdlflags = fullscreen ? SDL_FULLSCREEN : 0;

		// Have SDL set the video mode.
		if((surface = SDL_SetVideoMode(width, height, LOVE_SCREEN_DEPTH, sdlflags)) == 0)
		{
			std::cerr << "Could not set video mode: "  << SDL_GetError() << std::endl;
			return false;
		}

		currentMode.w = width;
		currentMode.h = height;

		return true;
	}

	int Graphics::getModes(lua_State * L)
	{
		SDL_Rect ** modes = SDL_ListModes(0, SDL_OPENGL | SDL_FULLSCREEN);

		if(modes == (SDL_Rect **)0 || modes == (SDL_Rect **)-1)
			return 0;

		int index = 1;

		lua_newtable(L);

		for(int i=0;modes[i];++i)
		{
			lua_pushinteger(L, index);
			lua_newtable(L);

			// Inner table attribs.

			lua_pushstring(L, "width");
			lua_pushinteger(L, modes[i]->w);
			lua_settable(L, -3);

			lua_pushstring(L, "height");
			lua_pushinteger(L, modes[i]->h);
			lua_settable(L, -3);

			// Inner table attribs end.

			lua_settable(L, -3);

			index++;
		}

		return 1;
	}

	SDL_Surface * Graphics::getSurface()
	{
		return surface;
	}

	Image * Graphics::newImage(love::image::ImageData *imagedata)
	{
		return new Image(imagedata, getSurface());
	}

	Font * Graphics::newFont(love::font::FontData * data)
	{
		Font * font = new Font(data, getSurface());

		// Load it and check for errors.
		if(!font)
		{
			delete font;
			return 0;
		}

		return font;
	}

	void Graphics::present()
	{
		if (surface == 0)
			return;
		SDL_Flip(surface);
	}

	void Graphics::clear()
	{
		if (surface == 0)
			return;
		boxRGBA(surface, 0, 0, currentMode.w, currentMode.h, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	}

	void Graphics::setColor(int r, int g, int b, int a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void Graphics::setBackgroundColor(int r, int g, int b)
	{
		backgroundColor.r = r;
		backgroundColor.g = g;
		backgroundColor.b = b;
		backgroundColor.a = 255;
	}

	void Graphics::setFont( Font * font )
	{
		if(currentFont != 0)
			currentFont->release();

		currentFont = font;

		if(font != 0)
			currentFont->retain();
	}

	Font * Graphics::getFont()
	{
		return currentFont;
	}

	void Graphics::print( const char * str, float x, float y )
	{
		if(currentFont != 0)
		{
			std::string text(str);

			if(text.find("\n") == std::string::npos)
				currentFont->print(text, x, y);
			else
			{
				int lines = 0;
				text = "";

				for(unsigned int i = 0; i < strlen(str); i++)
				{
					if(str[i] == '\n')
					{
						currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()));
						text = "";
						lines++;
					}
					else
						text += str[i];
				}

				if(text != "") // Print the last text (if applicable).
					currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()));
			}
		}
	}

	void Graphics::print( const char * str, float x, float y , float angle)
	{
		if(currentFont != 0)
		{
			std::string text(str);
			currentFont->print(text, x, y, angle, 1, 1);
		}
	}

	void Graphics::print( const char * str, float x, float y , float angle, float s)
	{
		if(currentFont != 0)
		{
			std::string text(str);
			currentFont->print(text, x, y, angle, s, s);
		}
	}

	void Graphics::print( const char * str, float x, float y , float angle, float sx, float sy)
	{
		if(currentFont != 0)
		{
			std::string text(str);
			currentFont->print(text, x, y, angle, sx, sy);
		}
	}

	void Graphics::printf( const char * str, float x, float y, float wrap, AlignMode align)
	{
		if(currentFont != 0)
		{
			std::string text = "";
			float width = 0;
			float lines = 0;

			for(unsigned int i = 0; i < strlen(str); i++)
			{
				if(str[i] == '\n')
				{
					switch(align)
					{
						case ALIGN_LEFT:
							currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
							break;

						case ALIGN_RIGHT:
							currentFont->print(text, (x + (wrap - currentFont->getWidth(text))), y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
							break;

						case ALIGN_CENTER:
							currentFont->print(text, ceil(x + ((wrap - currentFont->getWidth(text)) / 2)), ceil(y + (lines * currentFont->getHeight() * currentFont->getLineHeight())) );
							break;

						default: // A copy of the left align code. Kept separate in case an error message is wanted.
							currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
							break;
					}

					text = "";
					width = 0;
					lines++;
				}
				else
				{
					width += currentFont->getWidth(str[i]);

					if(width > wrap && text.find(" ") != std::string::npos) // If there doesn't exist a space, then ignore the wrap limit.
					{
						// Seek back to the nearest space and print that.
						unsigned int space = (unsigned int)text.find_last_of(' ');
						std::string temp = text.substr(0, space);

						switch(align)
						{
							case ALIGN_LEFT:
								currentFont->print(temp, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
								break;

							case ALIGN_RIGHT:
								currentFont->print(temp, (x + (wrap - currentFont->getWidth(temp))), y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
								break;

							case ALIGN_CENTER:
								currentFont->print(temp, ceil(x + ((wrap - currentFont->getWidth(temp)) / 2)), ceil(y + (lines * currentFont->getHeight() * currentFont->getLineHeight())) );
								break;

							default: // A copy of the left align code. Kept separate in case an error message is wanted.
								currentFont->print(temp, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
								break;
						}

						text = text.substr(space + 1);
						width = currentFont->getWidth(text);
						lines++;
					}

					text += str[i];
				}
			} // for

			if(text != "") // Print the last text (if applicable).
			{
				switch(align)
				{
					case ALIGN_LEFT:
						currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
						break;

					case ALIGN_RIGHT:
						currentFont->print(text, (x + (wrap - currentFont->getWidth(text))), y + (lines * currentFont->getHeight() * currentFont->getLineHeight()) );
						break;

					case ALIGN_CENTER:
						currentFont->print(text, ceil(x + ((wrap - currentFont->getWidth(text)) / 2)), ceil(y + (lines * currentFont->getHeight() * currentFont->getLineHeight())) );
						break;

					default: // A copy of the left align code. Kept separate in case an error message is wanted.
						currentFont->print(text, x, y + (lines * currentFont->getHeight() * currentFont->getLineHeight()));
						break;
				}
			}
		}
	}

	void Graphics::rectangle(DrawMode mode, int x, int y, int width, int height)
	{
		if (surface == 0)
			return;
		if (mode == DRAW_LINE)
			rectangleRGBA(surface, x, y, x+width, y+height, color.r, color.g, color.b, color.a);
		else if (mode == DRAW_FILL)
			boxRGBA(surface, x, y, x+width, y+height, color.r, color.g, color.b, color.a);
	}

	void Graphics::circle(DrawMode mode, int x, int y, int radius, int segments)
	{
		if (surface == 0)
			return;
		if (mode == DRAW_LINE)
			circleRGBA(surface, x, y, radius, color.r, color.g, color.b, color.a);
		else if (mode == DRAW_FILL)
			filledCircleRGBA(surface, x, y, radius, color.r, color.g, color.b, color.a);
	}

	void Graphics::line(float x1, float y1, float x2, float y2)
	{
		if (surface == 0)
			return;
		lineRGBA(surface, x1, y1, x2, y2, color.r, color.g, color.b, color.a);
	}

	int Graphics::polyline(lua_State * L)
	{
		if (surface == 0)
			return 0;
		// Get number of params.
		int args = lua_gettop(L);
		bool table = false;

		if (args == 1) { // we've got a table, hopefully
			int type = lua_type(L, 1);
			if (type != LUA_TTABLE)
				return luaL_error(L, "Function requires a table or series of numbers");
			table = true;
			args = lua_objlen(L, 1);
		}

		if (args % 2) // an odd number of arguments, no good for a polyline
			return luaL_error(L, "Number of vertices must be a multiple of two");

		// right, let's draw this polyline, then
		if (table) {
			lua_pushnil(L);
			if(lua_next(L, 1) == 0) return 0;
			float x1 = lua_tonumber(L, -1);
			lua_pop(L, 1); // pop value
			if(lua_next(L, 1) == 0) return 0;
			float y1 = lua_tonumber(L, -1);
			lua_pop(L, 1); // pop value
			while (true) {
				if(lua_next(L, 1) == 0) break;
				float x2 = lua_tonumber(L, -1);
				lua_pop(L, 1); // pop value
				if(lua_next(L, 1) == 0) break;
				float y2 = lua_tonumber(L, -1);
				lua_pop(L, 1); // pop value
				line(x1, y1, x2, y2);
				x1 = x2;
				y1 = y2;
			}
		} else {
			for (int i = 3; i < args; i+=2) {
				line(lua_tonumber(L, i-2), lua_tonumber(L, i-1), lua_tonumber(L, i), lua_tonumber(L, i+1));
			}
		}
		return 0;
	}

	void Graphics::point(float x, float y)
	{
		if (surface == 0)
			return;
		pixelRGBA(surface, x, y, color.r, color.g, color.b, color.a);
	}

	void Graphics::triangle(DrawMode mode, float x1, float y1, float x2, float y2, float x3, float y3)
	{
		if (surface == 0)
			return;
		if (mode == DRAW_LINE)
			trigonRGBA(surface, x1, y1, x2, y2, x3, y3, color.r, color.g, color.b, color.a);
		else if (mode == DRAW_FILL)
			filledTrigonRGBA(surface, x1, y1, x2, y2, x3, y3, color.r, color.g, color.b, color.a);
	}

	int Graphics::polygon(lua_State * L)
	{
		// Get number of params.
		int n = lua_gettop(L);

		// Need at least two params.
		if( n < 2 )
			return luaL_error(L, "Error: function needs at least two parameters.");

		DrawMode mode;

		const char * str = luaL_checkstring(L, 1);
		if(!getConstant(str, mode))
			return luaL_error(L, "Invalid draw mode: %s", str);

		// Get the type of the second argument.
		int luatype = lua_type(L, 2);

		// Perform additional type checking.
		switch(luatype)
		{
		case LUA_TNUMBER:
			if( n-1 < 6 ) return luaL_error(L, "Error: function requires at least 3 vertices.");
			if( ((n-1)%2) != 0 ) return luaL_error(L, "Error: number of vertices must be a multiple of two.");
			lua_pop(L, 1);
			n = lua_gettop(L);
			break;
		case LUA_TTABLE:
			if( (lua_objlen(L, 2)%2) != 0 ) return luaL_error(L, "Error: number of vertices must be a multiple of two.");
			n = lua_objlen(L, 2);
			break;
		default:
			return luaL_error(L, "Error: number type or table expected.");
		}

		int16_t *vx = new int16_t[n/2];
		int16_t *vy = new int16_t[n/2];
		int c = 0;

		switch(luatype)
		{
		case LUA_TNUMBER:
			for(int i = 1; i<n; i+=2)
			{
				vx[c] = lua_tointeger(L, i);
				vy[c] = lua_tointeger(L, i+1);
				c++;
			}
			break;
		case LUA_TTABLE:
			lua_pushnil(L);
			while (true)
			{
				if(lua_next(L, 2) == 0) break;
				vx[c] = lua_tointeger(L, -1);
				lua_pop(L, 1); // pop value
				if(lua_next(L, 2) == 0) break;
				vy[c] = lua_tointeger(L, -1);
				lua_pop(L, 1); // pop value
				c++;
			}
			break;
		}

		if (mode == DRAW_LINE)
			polygonRGBA(surface, vx, vy, c, color.r, color.g, color.b, color.a);
		else if (mode == DRAW_FILL)
			filledPolygonRGBA(surface, vx, vy, c, color.r, color.g, color.b, color.a);

		return 0;
	}

	void Graphics::setCaption(const char * caption)
	{
		SDL_WM_SetCaption(caption, 0);
	}
	
	int Graphics::getCaption(lua_State * L)
	{
		char * title = 0;
		SDL_WM_GetCaption(&title, 0);
		lua_pushstring(L, title);
		return 1;
	}

	int Graphics::getWidth()
	{
		return currentMode.w;
	}

	int Graphics::getHeight()
	{
		return currentMode.h;
	}

	bool Graphics::isCreated()
	{
		return (surface != 0);
	}

	Quad * Graphics::newQuad(int x, int y, int w, int h, int sw, int sh)
	{
		Quad::Viewport v;
		v.x = x;
		v.y = y;
		v.w = w;
		v.h = h;
		return new Quad(v, sw, sh);
	}
}
}
}
