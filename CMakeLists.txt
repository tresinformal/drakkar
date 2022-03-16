# CMakeLists.txt
cmake_minimum_required (VERSION 3.19)

# Integrate our local vcpkg install into CMake
set(CMAKE_TOOLCHAIN_FILE "${PROJECT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
if (WIN32)
    # the default is x86-windows -- 32Bit, really?
    set(VCPKG_TARGET_TRIPLET x64-windows)
endif()

project(game C CXX)
set(CMAKE_CXX_STANDARD 20)

# Let CMake make the call
# $> git submodule update --init --remote --recursive
# so the user doesn't have to.
#
# Optionally, you can/should add these lines to all the sub-folder CMakeLists.txt.
# That would take care about recursive submodules.
find_package(Git REQUIRED)
execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --remote --recursive
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
if (NOT GIT_SUBMOD_RESULT EQUAL "0")
    message(FATAL_ERROR "git submodule update --init --remote --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
endif()

add_subdirectory(src)
