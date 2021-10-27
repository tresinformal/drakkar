# [Install](install.md) Mac

  1. Download and install Qt Creator (once)
  2. Download and install SFML (once)

## 1. Download and install Qt Creator ([here](https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz))

Use all defaults, up until the Qt Maintenance tool is started.
Here, you will need to check two boxes:

 * 1. For the highest (stable) Qt version: 
      the highest MinGW :warning: remember this version of MinGW

![](qt_maintenance_tool_1_annotated.png)

 * 2. Under tools: that same MinGW :warning: remember this version of MinGW

![](qt_maintenance_tool_2.png)

## 2. Download and install SFML

 * Go to the SFML download page, [https://www.sfml-dev.org/download/sfml/2.5.0/](https://www.sfml-dev.org/download/sfml/2.5.0/)
 * Pick `MacOS Clang - 64-bit (OS X 10.7+, compatible with C++11 and libc++)` [here](https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz)

![](install_sfml_mac.png)

 * Unpack the tar, it will create a folder called `SFML-2.5.1-macos-clang`
 * Rename that folder to `SFML` and put it in your home folder. 
   Its path will be `/Users/[username]/SFML`
 * Copy the content of `SFML/Frameworks` folder into `/Library/Frameworks`.
   You will need root rights for this

