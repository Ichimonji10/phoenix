
TODO Items
==========

+ Port src/boot/boot.asm to WASM syntax. This will remove the dependency on NASM and allow the
  entire Phoenix system to be built with Open Watcom tools.

+ Set up (and document) a Phoenix test system based on Bochs, VMware, and/or Virtual PC. This
  step needs to be accomplished before any further "real" work can be done on the system.
  Setting up a real box on which to do Phoenix testing is awkward and inhibits development.

Documentation
-------------

+ Flesh out the Doxygen documentation.

+ Elaborate on the Developer's Guide.


Clean Up
--------

+ Normalize the test program file names in src/apps.

+ Remove all instances of camelNotation and replace them with names that are more in keeping
  with traditional_style.
