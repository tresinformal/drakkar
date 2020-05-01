# Install

## Linux

Type this in a terminal:

```
sudo apt-get install -qq qtcreator libqt5webkit5-dev qtdeclarative5-dev libqt5svg5* libqt5svg5-dev libsfml-dev
```

Done!

## Mac

### Download and install Qt Creator

![Pick these Qt Creator items](install_qt_creator.png)

### Download and install SFML

 * Go to the SFML download page, [https://www.sfml-dev.org/download/sfml/2.5.0/](https://www.sfml-dev.org/download/sfml/2.5.0/)
 * Pick `MacOS Clang - 64-bit (OS X 10.7+, compatible with C++11 and libc++)` [here](https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz)

![](install_sfml_mac.png)

 * Unpack the tar, it will create a folder called `SFML-2.5.1-macos-clang`
 * Rename that folder to `SFML` and put it in your home folder. 
   Its path will be `/Users/[username]/SFML`
 * Copy the content of `SFML/Frameworks` folder into `/Library/Frameworks`.
   You will need root rights for this

## Windows

### Download and install Qt Creator
 * Do not install the newer versions (Qt 5.12.0 or higher) if you are using a 32-bit SFML. 

![Pick these Qt Creator items](install_qt_creator.png)

### Download and install SFML

 * Go to the SFML download page, [https://www.sfml-dev.org/download/sfml/2.5.0/](https://www.sfml-dev.org/download/sfml/2.5.0/)
 * Pick `GCC 7.3.0 MinGW (DW2) - 32-bit` [here](https://www.sfml-dev.org/files/SFML-2.5.0-windows-gcc-7.3.0-mingw-32-bit.zip)

![Pick this SFML version](install_sfml.png)

 * Unpack the zip, it will create a folder called `SFML-2.5.0`
 * Rename that folder to `sfml`
 * Move that folder to within `C:/Qt`. Its new path will be `C:/Qt/sfml`

### Prepare Qt Creator

If you run the Qt Creator project now, you will get a `During Startup program exited with code 0xc0000135` error. This means it cannot find the path.

 * In Qt Creator, click 'Projects' (at the left vertical menu bar), go to 'Build', go to 'Build Environment', add to the `Path` variable: `;C:\Qt\sfml\bin`

If you have this line, remove it:

```
LIBS += -ljpeg # Remove this line
```

This is/was a working Qt Creator project file:

```
include(djog_unos_2018.pri)

# Entry point for user
SOURCES += main.cpp

# C++14
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

# High warning levels
# SFML goes bad with -Weffc++
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror

unix:!macx {
# Fix error: unrecognized option '--push-state--no-as-needed'
QMAKE_LFLAGS += -fuse-ld=gold
}

# Debug and release settings
CONFIG += debug_and_release
CONFIG(release, debug|release) {

  DEFINES += NDEBUG

  # GNU/Linux
  unix:!macx {
    # gprof
    QMAKE_CXXFLAGS += -pg
    QMAKE_LFLAGS += -pg
  }
}



CONFIG(debug, debug|release) {

  # GNU/Linux
  unix:!macx {
    # gcov
    QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
    LIBS += -lgcov

    # helgrind, for helgrind and memcheck
    QMAKE_LFLAGS += -pthread -Wl,--no-as-needed

    # UBSAN
    QMAKE_CXXFLAGS += -fsanitize=undefined
    QMAKE_LFLAGS += -fsanitize=undefined
    LIBS += -lubsan
  }
}

# High warning level, warnings are errors
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
QMAKE_CXXFLAGS += -Werror

# SFML
# GNU/Linux
unix:!macx {
  LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

  #LIBS += -L"/home/rafayel/SFML/lib"
  #INCLUDEPATH += "/home/rafayel/SFML/include"
  #DEPENDPATH += "/home/rafayel/SFML/include"
}

win32{
  INCLUDEPATH += C:/Qt/sfml/include
  LIBS += -LC:/Qt/sfml/lib
  CONFIG(release, debug|release):
  {
    #Audio Related Libs
    LIBS += -lsfml-audio
    LIBS += -lopenal32              #Dependency
    #SFML-Graphics Libs
    LIBS += -lsfml-graphics
    LIBS += -lfreetype              #Dependency

    #SFML-Window Libs
    LIBS += -lsfml-window
    LIBS += -lopengl32              #Dependency
    LIBS += -lgdi32                 #Dependency

    #SFML-System Libs
    LIBS += -lsfml-system
    LIBS += -lwinmm                 #Dependency
  }

  #Debug Configuration
  CONFIG(debug, debug|release):
  {
    #Audio Related Libs
    LIBS += -lsfml-audio-d
    LIBS += -lopenal32              #Dependency

    #SFML-Graphics Libs
    LIBS += -lsfml-graphics-d
    LIBS += -lfreetype              #Dependency
    #LIBS += -ljpeg                  #Dependency


    #SFML-Window Libs
    LIBS += -lsfml-window-d
    LIBS += -lopengl32              #Dependency
    LIBS += -lgdi32                 #Dependency

    #SFML-System Libs
    LIBS += -lsfml-system-d
    LIBS += -lwinmm                 #Dependency
  }
}

# Qt5
QT += core gui

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable

# Fixes
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
QMAKE_CXXFLAGS += -fext-numeric-literals

# Prevent Qt for failing with this error:
# qrc_[*].cpp:400:44: error: 'qInitResources_[*]__init_variable__' defined but not used
# [*]: the resource filename
QMAKE_CXXFLAGS += -Wno-unused-variable
```

