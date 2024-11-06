# Maize unit-testing

FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.7.1)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(test
        src/Application.test.cpp
        src/Event.test.cpp
        src/Vec2.test.cpp
        src/Rect.test.cpp
        src/Mesh.test.cpp
        src/Sprite.test.cpp
)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test PRIVATE
        MaizeEngine
        Catch2::Catch2WithMain
)
