cmake_minimum_required(VERSION 3.25)
project(PathToGlory)

set(CMAKE_CXX_STANDARD 17)

add_executable(PathToGlory main.cpp GameCharacter.cpp GameCharacter.h GameTile.cpp GameTile.h GameMap.cpp GameMap.h Game.cpp Game.h Animation.cpp Animation.h collision.cpp collision.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Users/HP/Desktop/SFML-2.6.0-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.0/lib/cmake/SFML)

find_package( SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Users/HP/Desktop/SFML-2.6.0-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.0/include)
target_link_libraries(PathToGlory sfml-system sfml-window sfml-graphics sfml-audio)