# Files
HEADERS += \
    action_type.h \
    enemy.h \
    environment.h \
    environment_type.h \
    food.h \
    food_type.h \
    game.h \
    game_resources.h \
    game_view.h \
    menu_button.h \
    menu.h \
    menu_view.h \
    player.h \
    player_shape.h \
    program_state.h \
    projectile_type.h \
    sound_type.h \
    game_options.h \
    color.h \
    shelter.h \
    projectile.h

SOURCES += \
    action_type.cpp \
    enemy.cpp \
    environment.cpp \
    environment_type.cpp \
    food.cpp \
    food_type.cpp \
    game.cpp \
    game_resources.cpp \
    game_view.cpp \
    main.cpp \
    menu_button.cpp \
    menu.cpp \
    menu_view.cpp \
    player.cpp \
    player_shape.cpp \
    program_state.cpp \
    projectile_type.cpp \
    sound_type.cpp \
    game_options.cpp \
    color.cpp \
    shelter.cpp \
    projectile.cpp

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
CONFIG += resources_big

# High warning levels
# SFML goes bad with -Weffc++
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

# A warning is an error
QMAKE_CXXFLAGS += -Werror

# Debug and release settings
CONFIG += debug_and_release
CONFIG(release, debug|release) {
  DEFINES += NDEBUG
}

# Qt5
QT += core gui

# SFML, default compiling
# GNU/Linux
unix:!macx {
  LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

  CONFIG(debug, debug|release) {
    # gcov
    QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
    LIBS += -lgcov
  }
}

win32{
  INCLUDEPATH += C:/Qt/sfml/include
  INCLUDEPATH += D:/Qt/sfml/include
  LIBS += -LC:/Qt/sfml/lib
  LIBS += -LD:/Qt/sfml/lib
  CONFIG(debug, debug|release) {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
  }
  CONFIG(release, debug|release) {
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
  }
  #LIBS += -lopenal32              #Dependency
  #LIBS += -lfreetype              #Dependency
  LIBS += -lopengl32              #Dependency
  LIBS += -lgdi32                 #Dependency
  LIBS += -lwinmm                 #Dependency
}

RESOURCES += \
    game_resources.qrc
