# Maize sandbox

add_executable(sandbox
        src/Sandbox.cpp
)

target_include_directories(sandbox PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(sandbox PRIVATE
        MaizeEngine
)
