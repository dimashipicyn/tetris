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
    font.h
    font.cpp
    provider.h
    provider.cpp
    state.h
    state.cpp
)