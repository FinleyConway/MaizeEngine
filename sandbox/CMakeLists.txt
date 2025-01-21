# Maize sandbox

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(sandbox
        src/Sandbox.cpp
        src/TestScene.h
        src/Rail.h
        src/MineCarMovement.cpp
        src/MineCarMovement.h
        src/Grid.h
        src/RailController.h
        src/RailSelector.h
        src/ChunkManager.h
        src/MineRailPlacement.cpp
        src/MineRailPlacement.h
        src/RailTile.h
        src/GridConversion.cpp
        src/GridConversion.h
        src/PlaceGridTile.h
        src/StaticHelperBase.h
        src/RailRotations.h
        src/RailTileChooser.cpp
        src/RailTileChooser.h
        src/FuzzyShape.h
)

target_include_directories(sandbox PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(sandbox PRIVATE
        MaizeEngine
)

if (MINGW)
    target_link_libraries(MaizeEngine PRIVATE -static-libgcc -static-libstdc++ -mwindows)
endif ()