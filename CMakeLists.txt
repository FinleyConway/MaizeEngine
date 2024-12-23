cmake_minimum_required(VERSION 3.28)
project(MaizeEngine LANGUAGES CXX)

# build flags
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(MAIZE_UNIT_TESTS "Build unit-test" OFF)
option(MAIZE_SANDBOX "Build sandbox" OFF)
option(MAIZE_ENABLE_LOGGING "Enable logging" ON)
option(MAIZE_ENABLE_ASSERTS "Enable asserts" ON)

if (MAIZE_ENABLE_LOGGING)
    add_definitions(-DENABLE_LOGGING)
endif ()
if (MAIZE_ENABLE_ASSERTS)
    add_definitions(-DENABLE_ASSERTS)
endif ()

include(FetchContent)
FetchContent_Declare(sfml GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 3.0.0)
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.13.0)
FetchContent_Declare(flecs GIT_REPOSITORY https://github.com/SanderMertens/flecs.git GIT_TAG v4.0.3)
FetchContent_MakeAvailable(sfml spdlog flecs)

add_library(MaizeEngine
        src/Maize.h

        src/Maize/Core/Application.h
        src/Maize/Core/Application.cpp
        src/Maize/Core/KeyCodes.h

        src/Maize/Core/Macros/PlatformDetection.h
        src/Maize/Core/Macros/Log.cpp
        src/Maize/Core/Macros/Log.h
        src/Maize/Core/Macros/Assert.h

        src/Maize/Math/Vec2.h
        src/Maize/Math/Rect.h

        src/Maize/Rendering/Mesh.cpp
        src/Maize/Rendering/Mesh.h
        src/Maize/Rendering/Sprite.cpp
        src/Maize/Rendering/Sprite.h
        src/Maize/Rendering/Renderer.cpp
        src/Maize/Rendering/Renderer.h

        src/Maize/Scene/Entity.h
        src/Maize/Scene/Components/Position.h
        src/Maize/Scene/Components/SceneComponents.h
        src/Maize/Scene/Scene.h
        src/Maize/Scene/SystemState.h
        src/Maize/Scene/SceneManager.cpp
        src/Maize/Scene/SceneManager.h
        src/Maize/Scene/Components/Rendering/Camera.h
        src/Maize/Scene/Components/Rendering/SpriteRenderer.h
        src/Maize/Scene/Components/Rendering/RenderingContext.h
        src/Maize/Scene/Systems/Rendering/RenderingSystem.cpp
        src/Maize/Scene/Systems/Rendering/RenderingSystem.h
)

target_include_directories(MaizeEngine PRIVATE src)
target_link_libraries(MaizeEngine PUBLIC SFML::Graphics spdlog::spdlog flecs::flecs_static)
target_compile_features(MaizeEngine PUBLIC cxx_std_20)

# add unit test
if (NOT BUILD_SHARED_LIBS AND MAIZE_UNIT_TESTS)
    add_subdirectory(test)
endif ()

# add sandbox
if (NOT BUILD_SHARED_LIBS AND MAIZE_SANDBOX)
    add_subdirectory(sandbox)
endif ()