cmake_minimum_required(VERSION 3.10)
project(raylib_ps1_game CXX)
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# raylib path (used for include and lib)
if(NOT DEFINED ENV{MSYS2_MINGW64_PATH})
    message(FATAL_ERROR "Please set the MSYS2_MINGW64_PATH environment variable to your MSYS2 mingw64 path (e.g., C:/msys64/mingw64)")
endif()

include_directories(
    $ENV{MSYS2_MINGW64_PATH}/include
    ${PROJECT_SOURCE_DIR}/src/include
)
link_directories($ENV{MSYS2_MINGW64_PATH}/lib)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(raylib_ps1_game ${SOURCES})
find_package(raylib REQUIRED)
target_link_libraries(raylib_ps1_game raylib opengl32 gdi32 winmm)

