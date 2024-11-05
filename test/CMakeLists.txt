# Maize unit-testing

#[[
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.7.1)
FetchContent_MakeAvailable(Catch2)

add_executable(test
)

target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test PRIVATE
        MaizeEngine
        Catch2::Catch2WithMain
)]]
