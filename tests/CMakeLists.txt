cmake_minimum_required(VERSION 3.14)
project(CompGeomAniket)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# So that we don't have to mention them in the "#include" line:
set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Because certain methods are defined outside the header files:
file(GLOB SOURCES
    ${INCLUDE_DIRECTORIES}/Angle.cpp
    ${INCLUDE_DIRECTORIES}/Line.cpp
    ${INCLUDE_DIRECTORIES}/Vector.cpp
)

add_executable(
    cga_tests
    cga_tests.cpp
    ${SOURCES}
)

target_include_directories(
    cga_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(
    cga_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(cga_tests)