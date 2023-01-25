# [Install](install.md) on Windows

  0. Get the right version
  1. Download and install Qt Creator (once)
  2. Download and install SFML (once)
  3. Let Qt Creator find SFML library (once per project file)

## 0. Get the right version

The hardest part about the installation is to realize that using
the correct version really matters,
in all three cases. Here is a zoom-in off all three cases.

The SFML version:

![](sfml_version_zoom.png)

The Qt version:

![](qt_maintenance_tool_1_zoom.png)

The Qt tool version:

![](qt_maintenance_tool_2_zoom.png)

Look how nice they match :-)

## 1. Download and install Qt Creator ([here](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5))

Use all defaults, up until the Qt Maintenance tool is started.
Here, you will need to check two boxes:

 * 1. Now Qt 5.14.2 belongs to Archive because it is an old version, before you can see it in the installer, we need to first show all the archived packages, following the steps on the screenshot.
![image](https://user-images.githubusercontent.com/57348932/192824914-dc3721e0-230c-41b7-a10a-09fb5d218d7c.png)

 * 2. Now we can see Qt 5.14.2, we tick it and expand it so that we could also see the correct version of MinGw (7.3.0).
![image](https://user-images.githubusercontent.com/57348932/192825152-980e947e-3cbc-46f7-a0b1-c0ac28f2a0a6.png)

## 2. Download and install SFML



 * Go to the SFML download page, 
   [https://www.sfml-dev.org/download/sfml/2.5.0/](https://www.sfml-dev.org/download/sfml/2.5.0/)
 * Pick the MinGW version you have installed and download the zip

![](sfml_version_annotated.png)

 * Unpack the zip, it will create a folder called `SFML-2.X.Y` (where X and Y are version numbers)
 * Rename that folder to `sfml`
 * Move that folder to within `C:/Qt`. Its new path will be `C:/Qt/sfml`

## 3. Let Qt Creator find SFML library

If you run the Qt Creator project now, 
you will get a `During Startup program exited with code 0xc0000135` error. 
This means it cannot find the path.

 * In Qt Creator, click 'Projects' (at the left vertical menu bar), 
   go to 'Build', 
   go to 'Build Environment', 
   add to the `Path` variable: `;C:\Qt\sfml\bin`

## 4. Clone the game and `magic_enum` library

Also do

```
git clone https://github.com/Neargye/magic_enum.git
```

in a folder *besides* the game folder, e.g. 

```
git clone https://github.com/tresinformal/game.git
git clone https://github.com/Neargye/magic_enum.git
```



