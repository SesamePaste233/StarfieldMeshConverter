# Setting Up Your Plugin

## **Installation**
1. Download Blender from its [official website](https://www.blender.org/). **Make sure to download a version that is higher than 3.5 and lower than 4.0**!
2. Download the Starfield Geometry Bridge plugin from [Nexus Mods](https://www.nexusmods.com/starfield/mods/4360)
3. Open Blender and Navigate to "Edit -> Preferences -> Addons -> Install". (See Image 1 & 2 below)
![Image 1](/hello/image1.png)
![Image 2](/hello/image2.png)
4. Install the Starfield Geometry Bridge plugin you just downloaded in the installation window.
5. Enable the plugin as is shown in Image 3.
![Image 3](/hello/image3.png)

## **Set Up Paths**
1. After successfully enabled the plugin, you should be able to find a new panel inside the Tool sidebar. (See the image below)
![Image 4](/hello/image4.png)
2. We only care about two folder paths for now. They are "**Export Folder**" and "**Assets Folder**".
3. **Export Folder** is the default folder that holds your exported files if their export paths are not specified. **Set this path to somewhere you won't forget**!
4. **Assets Folder** is the folder that has all the **loose files** extracted from ba2 archive files. The plugin will look for game assets as loose files in this folder. 
5. Since **Assets Folder** requires loose files, you should first **extract ba2 archives as loose files in a folder**, and then **set Assets Folder path to this folder**.
6. Currently the only game assets needed for this plugin are **mesh geometries**, which means only extracting "meshes01.ba2" and "meshes02.ba2" archives will just be enough. (Your Assets Folder should look like Image 5 below)
![Image 5](/hello/image5.png)


# Hello World!

## **Your First Mesh Export**
1. Create a Cube object in Blender and edit it however you like.
2. Select the Cube you just created and **make sure it's highlighted**!
3. Navigate to "Tool sidebar -> Export Starfield Mesh panel".
4. Toggle off "Export Datatypes -> Weights and Morph Data", since a simple cube is supposed to be neither weighted nor morphable.
5. Toggle on "After Export -> Open Export Folder" if you wish to see your exported file right after export. (You should have the same settings as is shown in Image 6 below)
![Image 7](/hello/image6.png)
6. Hit "Export .mesh" button, and your will see Cube.mesh file if the export is successful. Cheers!
![Image 8](/hello/image7.png)
7. **If you find this instruction hard to follow**, please familiar yourself with the basics of Blender. Watch a few Youtube videos and come back to this tutorial at any time.