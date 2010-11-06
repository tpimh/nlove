cmake_minimum_required (VERSION 2.8)

set(PHYSFS_INCLUDE /usr/include/)
set(PHYSFS_LIBRARY physfs)
set(LUA_INCLUDE /usr/include/lua5.1)
set(LUA_LIBRARY lua5.1)
set(SDL_INCLUDE /usr/include/SDL)
set(SDL_LIBRARY SDL SDL_image SDL_gfx SDL_mixer)
set(FREETYPE_INCLUDE /usr/include/freetype2)
set(FREETYPE_LIBRARY freetype)

set(LOVE_PLATFORM "\"Generic\"")
set(LOVE_LITTLE_ENDIAN 1)
set(LOVE_SCREEN_DEPTH 32)
set(LOVE_HAS_FINITE 1)
configure_file(common/config.h.cmake ../../../src/common/config.h)

include_directories(${PHYSFS_INCLUDE} ${LUA_INCLUDE} ${SDL_INCLUDE} ${FREETYPE_INCLUDE})
include_directories("." "modules")

add_library (love STATIC
	modules/filesystem/File.cpp
	modules/filesystem/FileData.cpp
	modules/filesystem/physfs/File.cpp
	modules/filesystem/physfs/Filesystem.cpp
	modules/filesystem/physfs/wrap_File.cpp
	modules/filesystem/physfs/wrap_FileData.cpp
	modules/filesystem/physfs/wrap_Filesystem.cpp
	modules/timer/sdl/Timer.cpp
	modules/timer/sdl/wrap_Timer.cpp
	modules/event/Event.cpp
	modules/event/sdl/Event.cpp
	modules/event/sdl/wrap_Event.cpp
	modules/keyboard/Keyboard.cpp
	modules/keyboard/sdl/Keyboard.cpp
	modules/keyboard/sdl/wrap_Keyboard.cpp
	modules/mouse/Mouse.cpp
	modules/mouse/sdl/Mouse.cpp
	modules/mouse/sdl/wrap_Mouse.cpp
	modules/joystick/Joystick.cpp
	modules/joystick/sdl/Joystick.cpp
	modules/joystick/sdl/wrap_Joystick.cpp
	modules/graphics/Drawable.cpp
	modules/graphics/Graphics.cpp
	modules/graphics/Image.cpp
	modules/graphics/Volatile.cpp
	modules/graphics/sdl/Font.cpp
	modules/graphics/sdl/Graphics.cpp
	modules/graphics/sdl/Glyph.cpp
	modules/graphics/sdl/Image.cpp
	modules/graphics/sdl/Quad.cpp
	modules/graphics/sdl/wrap_Font.cpp
	modules/graphics/sdl/wrap_Graphics.cpp
	modules/graphics/sdl/wrap_Image.cpp
	modules/graphics/sdl/wrap_Quad.cpp
	modules/image/EncodedImageData.cpp
	modules/image/ImageData.cpp
	modules/image/wrap_EncodedImageData.cpp
	modules/image/wrap_Image.cpp
	modules/image/wrap_ImageData.cpp
	modules/image/sdl/Image.cpp
	modules/image/sdl/ImageData.cpp
	modules/font/FontData.cpp
	modules/font/GlyphData.cpp
	modules/font/ImageRasterizer.cpp
	modules/font/Rasterizer.cpp
	modules/font/wrap_FontData.cpp
	modules/font/wrap_GlyphData.cpp
	modules/font/wrap_Rasterizer.cpp
	modules/font/freetype/Font.cpp
	modules/font/freetype/TrueTypeRasterizer.cpp
	modules/font/freetype/wrap_Font.cpp
	modules/audio/Source.cpp
	modules/audio/wrap_Audio.cpp
	modules/audio/wrap_Source.cpp
	modules/audio/null/Audio.cpp
	modules/audio/null/Source.cpp
	modules/audio/sdl/Audio.cpp
	modules/audio/sdl/Source.cpp
	modules/sound/Sound.cpp
	modules/sound/SoundData.cpp
	modules/sound/wrap_Decoder.cpp
	modules/sound/wrap_Sound.cpp
	modules/sound/wrap_SoundData.cpp
	modules/sound/lullaby/Decoder.cpp
	#modules/sound/lullaby/ModPlugDecoder.cpp
	#modules/sound/lullaby/Mpg123Decoder.cpp
	modules/sound/lullaby/Sound.cpp
	modules/sound/lullaby/VorbisDecoder.cpp
	modules/thread/sdl/Thread.cpp
	modules/thread/sdl/wrap_Thread.cpp
	modules/physics/Joint.cpp
	modules/physics/Shape.cpp
	modules/physics/box2d/Body.cpp
	modules/physics/box2d/CircleShape.cpp
	modules/physics/box2d/Contact.cpp
	modules/physics/box2d/DistanceJoint.cpp
	modules/physics/box2d/GearJoint.cpp
	modules/physics/box2d/Joint.cpp
	modules/physics/box2d/MouseJoint.cpp
	modules/physics/box2d/Physics.cpp
	modules/physics/box2d/PolygonShape.cpp
	modules/physics/box2d/PrismaticJoint.cpp
	modules/physics/box2d/PulleyJoint.cpp
	modules/physics/box2d/RevoluteJoint.cpp
	modules/physics/box2d/Shape.cpp
	modules/physics/box2d/World.cpp
	modules/physics/box2d/wrap_Body.cpp
	modules/physics/box2d/wrap_CircleShape.cpp
	modules/physics/box2d/wrap_Contact.cpp
	modules/physics/box2d/wrap_DistanceJoint.cpp
	modules/physics/box2d/wrap_GearJoint.cpp
	modules/physics/box2d/wrap_Joint.cpp
	modules/physics/box2d/wrap_MouseJoint.cpp
	modules/physics/box2d/wrap_Physics.cpp
	modules/physics/box2d/wrap_PolygonShape.cpp
	modules/physics/box2d/wrap_PrismaticJoint.cpp
	modules/physics/box2d/wrap_PulleyJoint.cpp
	modules/physics/box2d/wrap_RevoluteJoint.cpp
	modules/physics/box2d/wrap_Shape.cpp
	modules/physics/box2d/wrap_World.cpp
	modules/physics/box2d/graham/GrahamScanConvexHull.cpp
	modules/physics/box2d/Source/Collision/b2BroadPhase.cpp
	modules/physics/box2d/Source/Collision/b2CollideCircle.cpp
	modules/physics/box2d/Source/Collision/b2CollidePoly.cpp
	modules/physics/box2d/Source/Collision/b2Collision.cpp
	modules/physics/box2d/Source/Collision/b2Distance.cpp
	modules/physics/box2d/Source/Collision/b2PairManager.cpp
	modules/physics/box2d/Source/Collision/b2TimeOfImpact.cpp
	modules/physics/box2d/Source/Collision/Shapes/b2CircleShape.cpp
	modules/physics/box2d/Source/Collision/Shapes/b2PolygonShape.cpp
	modules/physics/box2d/Source/Collision/Shapes/b2Shape.cpp
	modules/physics/box2d/Source/Common/b2BlockAllocator.cpp
	modules/physics/box2d/Source/Common/b2Math.cpp
	modules/physics/box2d/Source/Common/b2Settings.cpp
	modules/physics/box2d/Source/Common/b2StackAllocator.cpp
	modules/physics/box2d/Source/Dynamics/b2Body.cpp
	modules/physics/box2d/Source/Dynamics/b2ContactManager.cpp
	modules/physics/box2d/Source/Dynamics/b2Island.cpp
	modules/physics/box2d/Source/Dynamics/b2World.cpp
	modules/physics/box2d/Source/Dynamics/b2WorldCallbacks.cpp
	modules/physics/box2d/Source/Dynamics/Contacts/b2CircleContact.cpp
	modules/physics/box2d/Source/Dynamics/Contacts/b2Contact.cpp
	modules/physics/box2d/Source/Dynamics/Contacts/b2ContactSolver.cpp
	modules/physics/box2d/Source/Dynamics/Contacts/b2PolyAndCircleContact.cpp
	modules/physics/box2d/Source/Dynamics/Contacts/b2PolyContact.cpp
	modules/physics/box2d/Source/Dynamics/Joints/b2DistanceJoint.cpp
	modules/physics/box2d/Source/Dynamics/Joints/b2GearJoint.cpp
	modules/physics/box2d/Source/Dynamics/Joints/b2Joint.cpp
	modules/physics/box2d/Source/Dynamics/Joints/b2MouseJoint.cpp
	modules/physics/box2d/Source/Dynamics/Joints/b2PrismaticJoint.cpp
	modules/physics/box2d/Source/Dynamics/Joints/b2PulleyJoint.cpp
	modules/physics/box2d/Source/Dynamics/Joints/b2RevoluteJoint.cpp
	common/b64.cpp
	common/Exception.cpp
	common/Matrix.cpp
	common/MemoryData.cpp
	common/Object.cpp
	common/Reference.cpp
	common/runtime.cpp
	common/utf8.cpp
	common/Vector.cpp
	common/wrap_Data.cpp
	libraries/luasocket/luasocket.cpp
	libraries/luasocket/libluasocket/auxiliar.c
	libraries/luasocket/libluasocket/buffer.c
	libraries/luasocket/libluasocket/except.c
	libraries/luasocket/libluasocket/inet.c
	libraries/luasocket/libluasocket/io.c
	libraries/luasocket/libluasocket/luasocket.c
	libraries/luasocket/libluasocket/mime.c
	libraries/luasocket/libluasocket/options.c
	libraries/luasocket/libluasocket/select.c
	libraries/luasocket/libluasocket/tcp.c
	libraries/luasocket/libluasocket/timeout.c
	libraries/luasocket/libluasocket/udp.c
	libraries/luasocket/libluasocket/unix.c
	libraries/luasocket/libluasocket/usocket.c
)

target_link_libraries(love ${PHYSFS_LIBRARY} ${LUA_LIBRARY} ${SDL_LIBRARY} ${FREETYPE_LIBRARY} mpg123 vorbis vorbisfile ogg modplug)

add_executable(nlove
	love.cpp
)

target_link_libraries(nlove love)
