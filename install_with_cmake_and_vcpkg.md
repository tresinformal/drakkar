# [Install](install.md) on Windows and use CMake to build

  0. Get the right version
  1. Download and install Qt Creator with CMAKE (once)
  2. Checkout to branch [CMAKE_attempts](https://github.com/tresinformal/drakkar/tree/CMAKE_attempts)
  3. Put your version of the branch up-to-date
  4. Update the vcpkg submodule (once)
  (For Qt creator users)
  5. Bootstrap vcpkg 
  6. open a new project on Qt creator by selectiung the CMakeLists.txt file in the repo

## 0. Get the right version

The hardest part about the installation is to realize that using
the correct version really matters. For this installation you will need to:

0. Install QtCreator 5.15 or higher
1. Make sure you are including CMake in the installation

## 1. Download and install Qt Creator ([here](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5))

Use all defaults, up until the Qt Maintenance tool is started.
Here, you will need to check two boxes:

 * 1. For the highest (stable) Qt version

 * 2. The following tools: 


## 2. Checkout to branch [CMAKE_attempts](https://github.com/tresinformal/drakkar/tree/CMAKE_attempts)
Do so by running `git checkout CMAKE_attempts`
## 3. Put your version of the branch up-to-date
Do so by running the command: `git pull`
## 4. Update the vcpkg submodule
Do so by running the command: `git submodule update --init`
## 5. Bootstrap vcpkg 
FRom the root of the repository enter the folder named `vcpkg` and double click on one of the 2 files named `bootstrap-vcpkg` (one is specifically for windows the othe works for any OS)
## 6. Open a project on Qtcreator using the CMakeLists.txt
`Choose File -> Open File or Project` and then select the file name `CMakeLists.txt` inside the repo. Configure the project as you see fit (possibly at least one configuration should be with MinGW). Qt should then be able to create your project.



