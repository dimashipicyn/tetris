include(FetchContent)

FetchContent_Declare(
  sdl2
  URL  https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-devel-2.30.9-VC.zip
)
FetchContent_Declare(
  sdl2-mixer
  URL  https://github.com/libsdl-org/SDL_mixer/releases/download/release-2.8.0/SDL2_mixer-devel-2.8.0-VC.zip
)
FetchContent_Declare(
  sdl2-image
  URL  https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip
)
FetchContent_Declare(
  sdl2-ttf
  URL  https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-VC.zip
)
FetchContent_MakeAvailable(sdl2 sdl2-mixer sdl2-image sdl2-ttf)