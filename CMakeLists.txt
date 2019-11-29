
  
#
# CI Hello World
#
# Copyright (C) 2017 Assured Information Security, Inc.
# Author: Rian Quinn        <quinnr@ainfosec.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.6)
project(game C CXX)

include(ExternalProject)
find_package(Git REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------

include_directories(include)
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/include)

# ------------------------------------------------------------------------------
# Catch
# ------------------------------------------------------------------------------

list(APPEND CATCH_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
)

ExternalProject_Add(
    catch
    GIT_REPOSITORY      https://github.com/Bareflank/catch.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${CATCH_CMAKE_ARGS}
    PREFIX              ${CMAKE_BINARY_DIR}/external/catch/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/catch/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/catch/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/catch/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/catch/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/catch/build
)

# ------------------------------------------------------------------------------
# Hippomocks
# ------------------------------------------------------------------------------

list(APPEND HIPPOMOCKS_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
)

ExternalProject_Add(
    hippomocks
    GIT_REPOSITORY      https://github.com/Bareflank/hippomocks.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${HIPPOMOCKS_CMAKE_ARGS}
    PREFIX              ${CMAKE_BINARY_DIR}/external/hippomocks/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/hippomocks/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/hippomocks/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/hippomocks/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/hippomocks/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/hippomocks/build
)

# ------------------------------------------------------------------------------
# GSL
# ------------------------------------------------------------------------------

list(APPEND GSL_CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
)

ExternalProject_Add(
    gsl
    GIT_REPOSITORY      https://github.com/Bareflank/GSL.git
    GIT_TAG             v1.2
    GIT_SHALLOW         1
    CMAKE_ARGS          ${GSL_CMAKE_ARGS}
    PREFIX              ${CMAKE_BINARY_DIR}/external/gsl/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/gsl/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/gsl/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/gsl/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/gsl/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/gsl/build
)
# ------------------------------------------------------------------------------
# Clang Tidy
# ------------------------------------------------------------------------------

if(ENABLE_CLANG_TIDY)

    find_program(CLANG_TIDY_BIN clang-tidy-6.0)
    find_program(RUN_CLANG_TIDY_BIN run-clang-tidy-6.0.py)

    if(CLANG_TIDY_BIN STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate clang-tidy-6.0")
    endif()

    if(RUN_CLANG_TIDY_BIN STREQUAL "RUN_CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate run-clang-tidy-6.0.py")
    endif()

    list(APPEND RUN_CLANG_TIDY_BIN_ARGS
        -clang-tidy-binary ${CLANG_TIDY_BIN}
        -header-filter=.*
        -checks=-*,cppcoreguidelines-*
    )

    add_custom_target(
        tidy
        COMMAND ${RUN_CLANG_TIDY_BIN} ${RUN_CLANG_TIDY_BIN_ARGS}
        COMMENT "running clang tidy"
    )

endif()
