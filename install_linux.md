# [Install](install.md) on Linux

Type this in a terminal:

```
sudo apt-get install -qq \
  qtcreator \
  qt5-qmake qt5-default \
  libqt5webkit5-dev qtdeclarative5-dev libqt5svg5* libqt5svg5-dev \
  libsfml-dev \
  libboost-all-dev \
  cppcheck \
  clang \
  g++-9 \
  clang-tidy \
  sloccount
```

 * Tip: peek at [.travis.yml](.travis.yml) which libraries are installed!

Also do

```
git clone https://github.com/Neargye/magic_enum.git
```

in a folder *besides* the game folder, e.g. 

```
git clone https://github.com/tresinformal/game.git
git clone https://github.com/Neargye/magic_enum.git
```



## Failures

### Cannot find `g++-9`

Do:

```
apt-cache search g++
```

Then install the `g++` with the highest version.

