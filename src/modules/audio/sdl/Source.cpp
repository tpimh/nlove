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

#include "Source.h"

#include <iostream>

namespace love
{
namespace audio
{
namespace sdl
{

	int Source::seek(SDL_RWops *context, int offset, int whence)
	{
		Source * thisS = (Source*) context->hidden.unknown.data1;
		return thisS->decoder->seek(offset);
	}

	int Source::read(SDL_RWops *context, void *ptr, int size, int maxnum)
	{
		Source * thisS = (Source*) context->hidden.unknown.data1;
		int decoded = thisS->decoder->decode();
		int readnum = (decoded < size*maxnum) ? decoded : size*maxnum;
		memcpy(ptr, thisS->decoder->getBuffer(), readnum);
		return readnum;
	}

	int Source::close(SDL_RWops *context)
	{
		Source * thisS = (Source*) context->hidden.unknown.data1;
		thisS->release();
		SDL_FreeRW(context);
	}

	Source::Source(love::sound::Decoder * decoder)
		: love::audio::Source(Source::TYPE_STREAM), decoder(decoder)
	{
		decoder->retain();
		rw = getRWops();
		music = Mix_LoadMUS_RW(rw);
	}

	Source::Source()
	: love::audio::Source(Source::TYPE_STATIC)
	{
	}

	Source::~Source()
	{
		decoder->release();
	}

	SDL_RWops * Source::getRWops()
	{
		SDL_RWops * rw;
		rw = SDL_AllocRW();
		if (rw)
		{
			rw->seek = seek;
			rw->read = read;
			rw->write = 0;
			rw->close = close;
			rw->hidden.unknown.data1 = (void*) this;
			this->retain();
		}
		return rw;
	}

	love::audio::Source * Source::copy()
	{
		this->retain();
		return this;
	}

	void Source::play()
	{
		if (type == TYPE_STREAM)
		{
			Mix_PlayMusic(music, looping);
		}
	}

	void Source::stop()
	{
		if (type == TYPE_STREAM)
		{
			Mix_HaltMusic();
		}
	}

	void Source::pause()
	{
		if (type == TYPE_STREAM)
		{
			Mix_PauseMusic();
		}
	}

	void Source::resume()
	{
		if (type == TYPE_STREAM)
		{
			Mix_ResumeMusic();
		}
	}

	void Source::rewind()
	{
		if (type == TYPE_STREAM)
		{
			Mix_RewindMusic();
		}
	}

	bool Source::isStopped() const
	{
		if (type == TYPE_STREAM)
		{
			return (!Mix_PlayingMusic() && Mix_PausedMusic());
		}
		return true;
	}

	bool Source::isFinished() const
	{
		if (type == TYPE_STREAM)
		{
			return (!Mix_PlayingMusic() && !Mix_PausedMusic());
		}
		return true;
	}

	void Source::update()
	{
	}

	void Source::setPitch(float pitch)
	{
		this->pitch = pitch;
	}

	float Source::getPitch() const
	{
		return pitch;
	}

	void Source::setVolume(float volume)
	{
		this->volume = volume;
	}

	float Source::getVolume() const
	{
		return volume;
	}

	void Source::setPosition(float *)
	{
	}

	void Source::getPosition(float *) const
	{
	}

	void Source::setVelocity(float *)
	{
	}

	void Source::getVelocity(float *) const
	{
	}

	void Source::setDirection(float *)
	{
	}

	void Source::getDirection(float *) const
	{
	}

	void Source::setLooping(bool looping)
	{
		this->looping = looping;
	}

	bool Source::isLooping() const
	{
		return looping;
	}

	bool Source::isStatic() const
	{
		return (type == TYPE_STATIC);
	}

} // sdl
} // audio
} // love
