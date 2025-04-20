cmake_minimum_required(VERSION 3.20.0)
project(tetris LANGUAGES C CXX)

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

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
	$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>

	$<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
	$<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
	$<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
)

if(EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES
		LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/assets@/"
    )
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_SOURCE_DIR}/emscripten/index.html"
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/index.html"
	)
endif()
