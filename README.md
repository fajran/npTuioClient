npTuioClient
============

npTuioClient is a TUIO client implemented as an NPAPI-based browser
plugins. It allows you to pass TUIO messages to into Javascript
environment inside your browser and therefore enables you to build a
multi-touch Javascript application!

The plugin works by capturing TUIO messages and forward them as
Javascript calls. When a touch event arrives, the plugin will call
`tuio_callback` function with touch type, locations, and other data as
parameters. Check the included example or
[TUIOjs](https://github.com/fajran/tuiojs) to see how to use them.

This plugin is built on top of
[reacTIVision's](http://reactivision.sourceforge.net/) TUIO client. It
is also built as NPAPI-plugin so it will never work on Internet
Explorer (unless it starts supporting the plugin architecture).

Limitation
----------

This plugin has only been tested on Mac OS X 10.7.5, but it is also
known to work on Linux. The Visual Studio project is currently broken
and hence this plugin will not work on Windows (unless somebody send
me a patch :-)

If you work on Windows, please try the [older
version](https://github.com/fajran/npTuioClient/tree/old).

Download
--------

* [Mac OS X](https://fajran.s3.amazonaws.com/github/npTuioClient/npTuioClient-1.5b2-mac.zip)

Compilation
-----------

### Linux

Go to the project directory and type `make`.

### Mac OS X

Open the Xcode project and build. I use Xcode 4.6.3 under Mac OS X 10.7.5

Installation
------------

### Linux

Put the plugin file `npTuioClient.so` under `~/.mozilla/plugins`.

### Mac OS X

Put the plugin bundle `npTuioClient.plugin` under `~/Library/Internet Plug-Ins/`.

Usage
-----

Install the plugin, open one of the example files on your browser and
start using your multi-touch display!

You can open multiple tabs or windows as long as they belong to the
same browser instance. The plugin can't be used from multiple browsers
at a time. This is because the TUIO Client library can only be started
once at a time.

