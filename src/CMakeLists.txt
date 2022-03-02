#add Qt library
find_package(Qt6 COMPONENTS Core REQUIRED)

#add sfml
set(SFML_DIR "C:/Qt/sfml/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

#include source files
file(GLOB src
     "${PROJECT_SOURCE_DIR}/src/*.cpp"
     "${PROJECT_SOURCE_DIR}/src/*.hpp"
     "${PROJECT_SOURCE_DIR}/src/*.h"
#     "${PROJECT_SOURCE_DIR}/*.qrc"
)


#add compiler flags for GNUCC
if(CMAKE_COMPILER_IS_GNUCC)
  add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror -g)
endif()

#include resource files:
# from https://stackoverflow.com/questions/17018477/cmake-adding-custom-resources-to-build-directory
# we don't want to copy if we're building in the source dir
#if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)

#    # list of files for which we add a copy rule
#    set(data_SHADOW "${PROJECT_SOURCE_DIR}/resources/*")

#    foreach(item IN LISTS data_SHADOW)
#        message(STATUS ${item})
#        add_custom_command(
#            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
#            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
#            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
#        )
#    endforeach()
#endif()

add_executable("game" ${src})

#link libraries to target
target_link_libraries(game PRIVATE sfml-graphics sfml-audio)
target_link_libraries(game PRIVATE Qt6::Core)
