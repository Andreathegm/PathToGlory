# 'Google_test' is the subproject name
project(Google_tests)
cmake_minimum_required(VERSION 3.5)


# 'lib' is the folder with Google Test sources
 add_subdirectory(lib)
#add_subdirectory(lib/googletest lib/googlemock )

set(gtest_SOURCE_DIR lib/googletest)
set(gmock_SOURCE_DIR lib/googlemock)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR} )
include_directories("C:/Users/HP/Desktop/SFML-2.6.0-windows-gcc-13.1.0-mingw-64-bit/SFML-2.6.0/include")


set(TEST_SOURCE_FILES GameCharacterTest.cpp GameTileTest.cpp GameMaptest.cpp MainMenuTest.cpp GameTest.cpp AnimationTest.cpp)
add_executable(RunTests ${TEST_SOURCE_FILES})
target_link_libraries(RunTests gtest gmock gtest_main gmock_main core sfml-system sfml-window sfml-graphics sfml-audio )
enable_testing()






