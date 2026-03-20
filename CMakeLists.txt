cmake_minimum_required(VERSION 3.16) # sets the oldest compatible CMake version
project(Taiko) # names project
set(CMAKE_CXX_STANDARD 17) # tells compiler to use C++17
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED) # searches for SFML library and its components
file(GLOB_RECURSE SOURCES "src/*.cpp") # collects all .cpp files in src directory and subdirectories into SOURCES variable
add_executable(taiko ${SOURCES}) # creates executable target named "taiko" using the collected source files
target_link_libraries(taiko sfml-graphics sfml-audio sfml-window sfml-system) # links the SFML libraries to the target