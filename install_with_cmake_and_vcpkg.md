# [Install](install.md) on Windows and use CMake to build

  0. Get the right version
  1. Download and install Qt Creator with CMAKE (once)
  2. Clone the repository remembering to update its submodules (vcpkg in particular) 'git clone https://github.com/tresinformal/game/tree/CMAKE_attempts --recursive'
  3. Update the vcpkg submodule (once)

## 0. Get the right version

The hardest part about the installation is to realize that using
the correct version really matters. For this installation you will need to:

0. Install QtCreator 5.15 or higher
1. Make sure you are including CMake in the installation

## 1. Download and install Qt Creator ([here](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5))

Use all defaults, up until the Qt Maintenance tool is started.
Here, you will need to check two boxes:

 * 1. For the highest (stable) Qt version: 
      the highest MinGW.

 * 2. Under tools: that same MinGW :warning: remember this version of MinGW

![](qt_maintenance_tool_2.png)

## 2. Update the vcpkg submodule

