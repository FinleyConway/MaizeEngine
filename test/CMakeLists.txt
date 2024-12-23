# Maize unit-testing

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.7.1)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(test
        src/Vec2.test.cpp
        src/Rect.test.cpp
        src/Mesh.test.cpp
        src/Sprite.test.cpp
        src/Renderer.test.cpp
        src/Entity.test.cpp
        src/SceneManager.test.cpp
        src/SpatialHashGrid.test.cpp
)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test PRIVATE
        MaizeEngine
        Catch2::Catch2WithMain
)
