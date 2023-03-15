# [Install](install.md) Mac

_Last updated: 02/03/2023 by @TheoPannetier on macOS 12.6_ 

  1. Download and install Qt Creator (once)
  2. Download and install SFML (once)

## 1. Download the Qt Installer ([here](https://www.qt.io/download-qt-installer))

Follow the install instructions using all the defaults until you reach Installation Folder. 
There, tick Qt 6.4 for desktop development and proceed with the installation.

## 2. Download and install SFML

 * Go to the SFML download page, [https://www.sfml-dev.org/download/sfml/2.5.1/](https://www.sfml-dev.org/download/sfml/2.5.1/) (or later than 2.5.1 if there is a new stable version)
 * Pick `MacOS Clang - 64-bit (OS X 10.7+, compatible with C++11 and libc++)` [here](https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz) (this should be the only option for mac)

 * Unpack the tar, it will create a folder called `SFML-2.5.1-macos-clang`
 * Rename that folder to `SFML` and put it in your home folder. 
   Its path will be `/Users/[username]/SFML`, where `[username]` is your
   username, resulting in, for example, `/Users/richel/SFML`.
   * Test that it works: 
     In a Terminal, 
     type `cd /Users/[username]/SFML`, where `[username]` is your
     username, resulting in, for example, `cd /Users/richel/SFML`.
     This should give no message.
     
## 3. Clone the game and `magic_enum` library

Clone the game repo in a folder you can easily access from the terminal. I suggest your home directory, e.g. `/Users/theo/`. 
Open the terminal, then type:

```
cd /Users/<your_username>/
git clone https://github.com/tresinformal/drakkar.git
```

Also do

```
git clone https://github.com/Neargye/magic_enum.git
```

in a folder *besides* the game folder, e.g. 

```
git clone https://github.com/tresinformal/game.git
git clone https://github.com/Neargye/magic_enum.git
```

# Running the game

Once all the components are installed, open QtCreator, select Open project. 
Then navigate to the folder where you cloned the game and select `game.pro`.
This file contains the instructions the compiler needs to run the game.

One last needed step is to tell the compiler where to find the SFML libraries on your computer.
On Mac, this unfortunately needs to be done separately for every computer*.
In `game.pro`, find a block of code inside `macx{ }`. Add two lines inside this block,

```
  INCLUDEPATH += /Users/[username]/SFML/include
```
and
```
  LIBS += -L/Users/[username]/SFML/lib
```

Then, hit the green triangle to build, wait for a while, and if there is no issue the game should open in a new window. Enjoy!

*If you do find a general solution, please share!

# Known issues

_If you encounter a problem with installation / building the game not listed here, and manage to solve it, please report it below so that later members can solve it easily :)_

- Upon building, I get error messages that look like: `Library not loaded: '@rpath/../Frameworks/freetype.framework/Versions/A/freetype'`. Make sure you have put the SFML folder in your home directory as indicated above, and that you have added the two lines of code to the `game.pro`. Then, if the issue persist, and you can read things like "freetype", "ogg", or "vorbis", the compiler is probably having trouble accessing extra SFML libraries that it expects to find in the lib subfolder. Go to SFML/extlibs, and copy everything in there into SFML/lib, and try to build again.


