npTuioClient
============

TUIO Client plugin for web browsers.

This is a TUIO Client implemented as an NPAPI-based browser plugin. It
uses [reacTIVision's](http://reactivision.sourceforge.net/) TUIO
Client as a base.

The plugin constantly calls a javascript function `tuio_callback`
whenever a new touch event arrives. Having this function called, you
can start using javascript to manipulate HTML, Canvas, SVG, etc!

Check also the included examples to see how to use this plugin.

The plugin has been tested and works on Firefox 3.0.10, Google Chrome
2.0.172.33, and Safari 4.0 on Windows XP. It also works under Firefox
3 on Ubuntu 8.04.

It doesn't work on Opera 9.64 on Windows XP nor Internet Explorer.
Since Internet Explorer can't use NPAPI-based plugin, the plugin has
to be ported first to an ActiveX-based plugin.

Download
--------

* [Windows](http://cloud.github.com/downloads/fajran/npTuioClient/npTuioClient-0.1-win.zip)
* [Linux](http://cloud.github.com/downloads/fajran/npTuioClient/npTuioClient-0.1.1-linux.tar.gz) (Ubuntu 8.04 i386)

Compilation
-----------

### Windows

Open the Visual C++ project/solution file and build. I use Visual C++
2008 Express Edition.

### Linux

TODO: The Makefile is broken.

Basically what you need is

* add `npapi`, `TuioClient`, and `TuioClient/oscpack` to include directories.
* add definition `OSC_HOST_LITTLE_ENDIAN` when compiling the source code.
* compile all *.cpp files except those that are under `win32` directory.
* compile as a shared library.

Installation
------------

### Windows

Put the plugin file `npTuioClient.dll` under Firefox'/Mozilla's
`plugin` directory. Mine is `C:\Program Files\Mozilla
Firefox\Plugins`.

### Linux

Put the plugin file `npTuioClient.so` under `~/.mozilla/plugins`.

Usage
-----

Open one of the example files on your browser and start using your
multi-touch display!

You can open multiple tabs or windows as long as they belong to the
same browser instance. The plugin can't be used from multiple browsers
at a time. This is because the TUIO Client library can only be started
once at a time.


