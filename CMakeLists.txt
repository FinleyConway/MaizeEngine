cmake_minimum_required(VERSION 3.28)
project(MaizeEngine LANGUAGES CXX)

# build flags
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(MAIZE_UNIT_TESTS "Build unit-test" OFF)
option(MAIZE_SANDBOX "Build sandbox" OFF)
option(MAIZE_ENABLE_LOGGING "Enable logging" ON)
option(MAIZE_ENABLE_ASSERTS "Enable asserts" ON)
option(MAIZE_ENABLE_BENCHMARK "Enable benchmarking" OFF)

if (MAIZE_ENABLE_LOGGING)
    add_definitions(-DENABLE_LOGGING)
endif ()
if (MAIZE_ENABLE_ASSERTS)
    add_definitions(-DENABLE_ASSERTS)
endif ()
if (MAIZE_ENABLE_BENCHMARK)
    add_definitions(-DENABLE_PROFILING)
endif()

include(FetchContent)
FetchContent_Declare(sfml GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 3.0.0)
FetchContent_Declare(imgui-sfml GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git GIT_TAG v3.0)
FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui.git GIT_TAG v1.91.6)
FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.13.0)
FetchContent_Declare(flecs GIT_REPOSITORY https://github.com/SanderMertens/flecs.git GIT_TAG v4.0.3)

FetchContent_MakeAvailable(sfml spdlog flecs imgui)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_MakeAvailable(imgui-sfml)

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
        src/Maize/Scene/Scene.h
        src/Maize/Scene/SystemState.h
        src/Maize/Scene/SceneManager.cpp
        src/Maize/Scene/SceneManager.h
        src/Maize/Scene/Components/Rendering/Camera.h
        src/Maize/Scene/Components/Rendering/SpriteRenderer.h
        src/Maize/Scene/Components/Rendering/RenderingContext.h
        src/Maize/Scene/Systems/Rendering/RenderingSystem.cpp
        src/Maize/Scene/Systems/Rendering/RenderingSystem.h
        src/Maize/Utils/SpatialHashGrid.cpp
        src/Maize/Utils/SpatialHashGrid.h
        src/Maize/Scene/Systems/Rendering/RenderComponentChange.cpp
        src/Maize/Scene/Systems/Rendering/RenderComponentChange.h
        src/Maize/Scene/Components/Rendering/DeferredRenderable.h
        src/Maize/Scene/Components/Input.h
        src/Maize/Scene/Systems/InputSystem.cpp
        src/Maize/Scene/Systems/InputSystem.h
        src/Maize/Core/Instrumentor.h
        src/PrecompiledHeader.cpp
        src/Maize/Math/Math.h
        src/Maize/Scene/Components/Rendering/MeshRenderer.h
        src/Maize/Scene/Components/Active.h
        src/Maize/Scene/Components/ChangeScene.h
)

target_include_directories(MaizeEngine PRIVATE src)
target_link_libraries(MaizeEngine PUBLIC SFML::Graphics spdlog::spdlog flecs::flecs_static ImGui-SFML::ImGui-SFML)
target_compile_features(MaizeEngine PUBLIC cxx_std_20)
target_precompile_headers(MaizeEngine PUBLIC src/PrecompiledHeader.h)

# add unit test
if (NOT BUILD_SHARED_LIBS AND MAIZE_UNIT_TESTS)
    add_subdirectory(test)
endif ()

# add sandbox
if (NOT BUILD_SHARED_LIBS AND MAIZE_SANDBOX)
    add_subdirectory(sandbox)
endif ()