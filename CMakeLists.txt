 cmake_minimum_required(VERSION 3.8)
 set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find_program(CLANG_TIDY_BIN clang-tidy-6.0)
# find_program(RUN_CLANG_TIDY_BIN run-clang-tidy-6.0.py)

# if(CLANG_TIDY_BIN STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
    # message(FATAL_ERROR "unable to locate clang-tidy-6.0")
# endif()

# if(RUN_CLANG_TIDY_BIN STREQUAL "RUN_CLANG_TIDY_BIN-NOTFOUND")
    # message(FATAL_ERROR "unable to locate run-clang-tidy-6.0.py")
# endif()

# list(APPEND RUN_CLANG_TIDY_BIN_ARGS
    # -clang-tidy-binary ${CLANG_TIDY_BIN}
    # -header-filter=.*
    # -checks=-*,cppcoreguidelines*
# )

# add_custom_target(
    # tidy
    # COMMAND ${RUN_CLANG_TIDY_BIN} ${RUN_CLANG_TIDY_BIN_ARGS}
    # COMMENT "running clang tidy"
# )

project("game" C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SFML_DIR "C:/Qt/sfml/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(MINGW)
set(CMAKE_PREFIX_PATH "C:/Qt/6.1.1/mingw81_64")
elseif(MSVC)
set(CMAKE_PREFIX_PATH "C:/Qt/6.1.1/msvc2019_64")
endif()

find_package(Qt6 COMPONENTS Core REQUIRED)

if(UNIX)
set(CMAKE_BUILD_TYPE "Debug")
endif()


file(GLOB src
     "${PROJECT_SOURCE_DIR}/*.cpp"
     "${PROJECT_SOURCE_DIR}/*.hpp"
     "${PROJECT_SOURCE_DIR}/*.h"
)

if(CMAKE_COMPILER_IS_GNUCC)
  add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror -g)
endif()

add_executable("game" ${src})

target_link_libraries(game PRIVATE sfml-graphics sfml-audio)
target_link_libraries(game PRIVATE Qt6::Core)
