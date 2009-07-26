/**
* Copyright (c) 2006-2009 LOVE Development Team
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

namespace love
{
namespace audio
{
namespace null
{

	Source::Source()
	{
	}

	Source::Source(Audible * audible)
	{
		setAudible(audible);
	}

	Source::~Source()
	{
	}

	void Source::play()
	{
	}

	void Source::stop()
	{
	}

	void Source::pause()
	{
	}

	void Source::resume()
	{
	}

	void Source::rewind()
	{
	}

	bool Source::isFinished() const
	{
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

} // null
} // audio
} // love
