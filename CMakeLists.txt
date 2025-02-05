cmake_minimum_required(VERSION 3.14)

project(CompGeomAniket)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# outputting executables into ./bin:
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# So that we don't have to mention them in the "#include" line:
set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(TESTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Because certain methods are defined outside the header files:
file(GLOB SOURCES
    ${INCLUDE_DIRECTORIES}/*.cpp
)

add_executable(
    dummy
    src/dummy.cpp
    ${SOURCES}
)

target_include_directories(
    dummy PRIVATE
    ${INCLUDE_DIRECTORIES}
)