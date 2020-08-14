# CMakeList.txt : CMake project for CPPFinalProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CPPFinalProject")

# Add source to this project's executable.
add_executable (CPPFinalProject "CPPFinalProject.cpp"  "Card.cpp" "Card.h" "Game.cpp" "Game.h")

# TODO: Add tests and install targets if needed.

target_include_directories(CPPFinalProject PUBLIC "./SFML-2.5.1/include" )
target_link_directories(CPPFinalProject PUBLIC "./SFML-2.5.1/lib")

target_link_libraries(CPPFinalProject PUBLIC "sfml-system-d" "sfml-audio-d" "sfml-window-d" "sfml-graphics-d")