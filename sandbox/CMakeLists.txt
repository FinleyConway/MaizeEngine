# Maize sandbox

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(sandbox
        src/Sandbox.cpp
        src/Scenes/TestScene.h
        src/Utils/Rail.h
        src/Systems/MineCarMovement.cpp
        src/Systems/MineCarMovement.h
        src/Components/Grid.h
        src/Components/RailController.h
        src/Components/RailSelector.h
        src/Components/ChunkManager.h
        src/Systems/MineRailPlacement.cpp
        src/Systems/MineRailPlacement.h
        src/Utils/RailTile.h
        src/Utils/GridConversion.cpp
        src/Utils/GridConversion.h
        src/Components/PlaceChunkTile.h
        src/Utils/StaticHelperBase.h
        src/Components/RailRotations.h
        src/Systems/RailTileChooser.cpp
        src/Systems/RailTileChooser.h
        src/Utils/FuzzyShape.h
        src/Utils/PlaceRailData.h
        src/Utils/RailTurnDirection.h
)

target_include_directories(sandbox PRIVATE src ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(sandbox PRIVATE
        MaizeEngine
)

if (MINGW)
    target_link_libraries(MaizeEngine PRIVATE -static-libgcc -static-libstdc++ -mwindows)
endif ()