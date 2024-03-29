#add Qt library
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)

#add sfml
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

#add compiler flags for GNUCC
if(CMAKE_COMPILER_IS_GNUCC)
  add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror -g)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#include source files
file(GLOB src
     "${PROJECT_SOURCE_DIR}/src/*.cpp"
     "${PROJECT_SOURCE_DIR}/src/*.hpp"
     "${PROJECT_SOURCE_DIR}/src/*.h"
)

#add resource files
qt_add_resources(resources_for_game "${PROJECT_SOURCE_DIR}/resources/game_resources.qrc")

add_executable("game" ${src} ${resources_for_game})

#link libraries to target
target_link_libraries(game PRIVATE sfml-graphics sfml-audio)
target_link_libraries(game PRIVATE Qt${QT_VERSION_MAJOR}::Core)
