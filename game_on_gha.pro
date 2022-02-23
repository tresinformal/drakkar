# This is the project file used on Travis.
#
# Use 'game.pro' to run the game!
#
# This .pro file is used for codecov and profiling

win32{
  error(Do not run this .pro file on a Windows computer)
  error(Use 'game.pro' to run the game)
  error(This .pro file is used to be run on Travis)
}

# All files
include(game.pri)
include(game_view.pri)

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

# To get it working on GitHub Actions,
# we cannot use any SFML thingies
DEFINES += LOGIC_ONLY

# Debug and release settings
CONFIG += debug_and_release
CONFIG(release, debug|release) {
  DEFINES += NDEBUG
}

# Qt5
QT += core gui

# SFML, default compiling
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CONFIG(debug, debug|release) {
  # High warning levels
  QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

  # A warning is an error
  QMAKE_CXXFLAGS += -Werror

  # gcov
  QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
  LIBS += -lgcov
}


