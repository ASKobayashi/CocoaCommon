Cocoa Common
========
This is a set of routines that I use in all my cocoa projects.

Usage
-----
To enable logging functionality, set the preprocessor cflag DEBUG=1 for debug builds
and 0 for release builds.


Logging
-------
DLog works exactly like NSLog, but with the following enhancements:
    * All DLog messages are disabled when building release mode
    * DLog messages can be turned on and off on the fly by calling AALogEnabled
    * Messages output is enhanced to include:
      * File Called DLog was in
      * Line Number DLog was called in
      * LOG Level (By using AALogWarn, AALogErr, AALogDump)

ALog includes the message output enhancements of DLog, but will still be printed in 
release mode.

Assertions
----------
The following assertions are included:
    * AAPRECONDITION
    * AAPOSTCONDITION
    * AAINVARIANT
    * AAASERT

These are used to assert that conditions are true, and if in debug mode, abort 
program execution if the assertion failed.

Who are you?
------------

I'm [Aaron Kobayashi][askobayashi] and I'm a coder.

[askobayashi]:http://ASKobayashi.com 
