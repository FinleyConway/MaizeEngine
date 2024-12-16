cmake_minimum_required(VERSION 3.28)
project(MaizeEngine LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# build flags
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(MAIZE_UNIT_TESTS "Build unit-test" OFF)
option(MAIZE_SANDBOX "Build sandbox" OFF)

# macro flags
option(ENABLE_LOGGING "Enable logging" ON)
option(ENABLE_ASSERTS "Enable asserts" ON)
if (ENABLE_LOGGING)
    add_definitions(-DENABLE_LOGGING)
endif ()
if (ENABLE_ASSERTS)
    add_definitions(-DENABLE_ASSERTS)
endif ()

include(FetchContent)
FetchContent_Declare(sfml GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1)
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
target_link_libraries(MaizeEngine PUBLIC sfml-graphics spdlog::spdlog flecs::flecs_static)
target_compile_features(MaizeEngine PUBLIC cxx_std_20)

# add unit test
if (NOT BUILD_SHARED_LIBS AND MAIZE_UNIT_TESTS)
    add_subdirectory(test)
endif ()

# add sandbox
if (NOT BUILD_SHARED_LIBS AND MAIZE_SANDBOX)
    add_subdirectory(sandbox)
endif ()

if(WIN32)
    add_custom_command(
            TARGET main
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
            VERBATIM
    )
endif()