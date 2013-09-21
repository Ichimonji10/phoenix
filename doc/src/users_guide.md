Phoenix User's Guide
====================

Create a Boot Disk
------------------

### Requirements

* Open Watcom with 16bit support
* NASM
* A floppy disk

### Instructions

1. Put a floppy disk in the drive.
2. Navigate to the Phoenix src directory.
3. Type "wmake"
4. Navigate to the Phoenix src\boot directory.
5. Type "nasm boot.asm -o boot.bin".
6. Type "debug boot.bin".
7. Type "W 100 0 0 1".
8. Type "Q" for quit.
9. Type "wmake".
10. Type "..\tools\memalign loader.com".
11. Copy the new bloader.com file to the floppy disk.
12. Copy any of the apps that you want to be able to run on to the floppy.

Play a Game
-----------

1. Make sure the computer is off.
2. Place a phoenix floppy disk containing phoenix executables in the floppy
   drive.
3. Turn the computer on.
4. If you have more than one phoenix executable on the disk a menu will appear.
5. Select the game you want to play by hitting the corresponding number from
   zero to nine on the keyboard.
6. Follow any additional instructions from the game.

Write an Application
--------------------

1. Create a main() similar to those in the sample applications and tests which
   sets up the threads and modules which you'll need to use.  Remember to set up
   the threads you'll be writing as well.
2. Write your application in the threads you created for yourself.  If you're
   only using one thread you can treat it as if it were your main() in a
   traditional application.  If you're using multiple threads you can treat them
   like you usually would.
3. All the libraries that you have access to are located in RTL.  If you need
   functionality that wouldn't need to be a module, then you could add that to
   the RTL and use it.  This has been done with some of the basic string
   functions.  If the functionality would require a module, such as needed to
   interact with a piece of hardware, then you should consult the developers
   guide and create the module.
4. Currently you can directly call functions within modules.  This may be useful
   for testing purposes, but otherwise should be avoided as future updates may
   break your program.
