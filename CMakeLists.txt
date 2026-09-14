cmake_minimum_required(VERSION 4.0)
project(OOD_L1_Shapes)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

find_package(Catch2 3 REQUIRED)

set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.2/lib/cmake/SFML")
find_package(SFML 3 COMPONENTS Graphics REQUIRED)

file(GLOB_RECURSE SOURCES "./src/*.cpp" "./src/*.h")
list(FILTER SOURCES EXCLUDE REGEX ".*/test/.*")
add_library(lib_utils ${SOURCES})
target_link_libraries(lib_utils PUBLIC SFML::Graphics)

add_executable(OOD_L1_Shapes main.cpp)
target_link_libraries(OOD_L1_Shapes PRIVATE lib_utils)
target_link_options(OOD_L1_Shapes PRIVATE "LINKER:-all_load")

add_executable(ShapeStorageTest src/model/shapeStorage/test/Test.cpp)
target_link_libraries(ShapeStorageTest PRIVATE lib_utils)
target_link_libraries(ShapeStorageTest PRIVATE Catch2::Catch2WithMain)

add_executable(StrategyTest src/strategy/impl/test/Test.cpp)
target_link_libraries(StrategyTest PRIVATE lib_utils)
target_link_libraries(StrategyTest PRIVATE Catch2::Catch2WithMain)

add_executable(PictureTest src/model/picture/test/Test.cpp)
target_link_libraries(PictureTest PRIVATE lib_utils)
target_link_libraries(PictureTest PRIVATE Catch2::Catch2WithMain)
target_link_options(PictureTest PRIVATE "LINKER:-all_load")

add_executable(GfxTest src/gfx/impl/test/Test.cpp
        src/gfx/abstract/ICanvas.h
        src/parser/Parser.cpp
        src/parser/Parser.h
)
target_link_libraries(GfxTest PRIVATE lib_utils)
target_link_libraries(GfxTest PRIVATE Catch2::Catch2WithMain)
target_link_options(GfxTest PRIVATE "LINKER:-all_load")

