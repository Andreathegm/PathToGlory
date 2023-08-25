cmake_minimum_required(VERSION 3.5)
project(PathToGlory)

set(CMAKE_CXX_STANDARD 17)

# Define the source files for your project
set(SOURCE_FILES
        main.cpp
        GameCharacter.cpp GameCharacter.h
        GameTile.cpp GameTile.h
        GameMap.cpp GameMap.h
        Game.cpp Game.h
        Animation.cpp Animation.h
        collision.cpp collision.h
        MainMenu.cpp MainMenu.h
        )

# Locate the SFML package
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Users/HP/Desktop/SFML-2.6.0-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.0/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

# Include directories for SFML headers
include_directories("C:/Users/HP/Desktop/SFML-2.6.0-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.0/include")
add_subdirectory(Google_tests)
# Create the core library
add_library(core ${SOURCE_FILES} )

# Create the main executable and link with the core library and SFML
add_executable(PathToGlory ${SOURCE_FILES}  )
target_link_libraries(PathToGlory  sfml-system sfml-window sfml-graphics sfml-audio )
