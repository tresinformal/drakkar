# This is the general project file,
# to be used to simply run the game.
#
# Other .pro files are used for specific tasks,
# such as codecov or profiling

# All files are in here, the rest are just settings
include(game.pri)
include(game_view.pri)

# Use the C++ version that all team members can use
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

# High warning levels
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic


# Debug and release settings
CONFIG += debug_and_release
CONFIG(release, debug|release) {
  DEFINES += NDEBUG
}
CONFIG(debug, debug|release) {
  # A warning is an error, only in debug mode
  QMAKE_CXXFLAGS += -Werror
}

# Qt5
QT += core gui

# GNU/Linux
unix:!macx {
  LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
}

macx {
  INCLUDEPATH += /Users/johti53/SFML/include
  LIBS += -L/Users/johti53/SFML/lib \
      -lsfml-system \
      -lsfml-window \
      -lsfml-graphics \
      -lsfml-audio \
      -lsfml-network
}

win32{
  INCLUDEPATH += C:/Qt/sfml/include
  INCLUDEPATH += D:/Qt/sfml/include
  INCLUDEPATH += C:/DEV/SFML-2.5.1/include
  LIBS += -LC:/Qt/sfml/lib
  LIBS += -LD:/Qt/sfml/lib
  LIBS += -LC:/DEV/SFML-2.5.1/lib
  CONFIG(debug, debug|release) {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
  }
  CONFIG(release, debug|release) {
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
  }
  LIBS += -lopengl32
  LIBS += -lgdi32
  LIBS += -lwinmm
}
