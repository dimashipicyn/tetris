add_subdirectory(math)
target_sources(${PROJECT_NAME} PUBLIC
    app.h
    app.cpp
    texture.h
    texture.cpp
    assets.h
    assets.cpp
    renderer.h
    renderer.cpp
    scene_object.h
    scene_object.cpp
    scene.h
    sprite.h
    sprite.cpp
)