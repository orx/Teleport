Orx Sample #1 : Seamless Screen Edge Teleportation
==================================================

This sample has been made using [orx, portable game engine](https://orx-project.org).

It is based on the template that ships with `orx` (by calling the `init` tool) with minimal modifications, [as can be seen in the demonstration video](https://youtu.be/wo6o8BAMnM0).

![Screenshot](Screenshot.png)


How to build
------------

In order to build this sample, you'll need to have a working installation of orx.
If you already have one, you can simply use the build files adapted to your OS/IDE in the `build/` directory.

If you do not already have installed and compiled orx, please follow those steps:

- Clone the `orx` repository at https://github.com/orx/orx
- Run `setup.bat`/`setup.sh` at its root to sync the dependencies and create the build/project files
- Use the build files in the `code/build/` directory that fit your OS/IDE and compile the `Release` configuration

You now have a working orx installation but you might need to logout/login or restart your shell/environment for the `ORX` environment variable to be updated.

Once done, simply build the `Release` configuration of this sample (note: make sure to match 32bit/64bit with the version of orx you built).


How does it work?
-----------------

The source code can be found in `src/Teleporc.cpp`.

During the initialization phase two main things happen:

- We create all the viewports defined in data in the `Teleport.ViewportList` config value
- We create a single object named `Scene`

During the update phase (ie. every frame), we iterate over all the objects that are part of the group `Character` and update their position to make sure they stay inside the camera boundaries.

At this point, it's a trivial behavior that doesn't account for seamless wrapping.

Everything else is defined on the data side, in the `data/config/Teleport.ini` config file. In there we can find:

- The definition of the `Scene` object and all its children (1 background `Map` and 8 `Robots`)
- The definition of the `Map` object and all the `Robots`
- The definition of all the viewports, which are key for the seamless wrapping visual effect

[More details in the video.](https://youtu.be/wo6o8BAMnM0)


Useful links:
-------------

Website: https://orx-project.org  
Wiki: https://orx-project.org/wiki  
Code repository: https://github.com/orx/orx  
Come chat with us: https://gitter.im/orx/orx  
Forum: https://orx-project.org/forum  
Twitter: https://twitter.com/orxproject  
