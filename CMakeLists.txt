cmake_minimum_required(VERSION 3.20.0)
project(tetris LANGUAGES C CXX)

add_subdirectory(third_party)

add_executable(${PROJECT_NAME})
add_subdirectory(source)

if (MSVC)
target_compile_options(${PROJECT_NAME} PUBLIC /Wall)
else()
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -Werror -pedantic)
endif()

target_include_directories(${PROJECT_NAME}
PRIVATE
	"source"
)

list(APPEND CMAKE_PREFIX_PATH out/clang-debug/_deps/sdl2-src)
list(APPEND CMAKE_PREFIX_PATH out/clang-debug/_deps/sdl2-image-src)
list(APPEND CMAKE_PREFIX_PATH out/clang-debug/_deps/sdl2-mixer-src)
list(APPEND CMAKE_PREFIX_PATH out/clang-debug/_deps/sdl2-ttf-src)

find_package(SDL2)
find_package(SDL2_image)
find_package(SDL2_mixer)
find_package(SDL2_ttf)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	SDL2::SDL2
	SDL2_image::SDL2_image
	SDL2_mixer::SDL2_mixer
	SDL2_ttf::SDL2_ttf
)

add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
		"$<TARGET_FILE:SDL2::SDL2>"
		"$<TARGET_FILE:SDL2_image::SDL2_image>"
		"$<TARGET_FILE:SDL2_mixer::SDL2_mixer>"
		"$<TARGET_FILE:SDL2_ttf::SDL2_ttf>"
		"$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    VERBATIM
)
