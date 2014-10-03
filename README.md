ExOS
====

A bare bones x64 UEFI operating system written in C++14 with a focus on clean, easily readable code.

### Building

Currently, ExOS can only be build on OS X. 
Support for building on Linux is planned.

Building ExOS requires a working installation of `clang` and OS X's `ld`.
Furthermore, since ExOS is designed to be a UEFI "Application" and OS X's ld is incapable
of generating PE/COFF files as required by UEFI, a small utility called `mtoc` is needed.
Instructions on how to obtain it are here: http://tianocore.sourceforge.net/wiki/Xcode.  
Copy the binary to the working directory.

As we're building a bare bones executable but still use standard C++ headers suitable for use in a
freestanding environment, we need to export the path to the standard C++ header files.  
Run `export CPLUS_INCLUDE_PATH=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1`.  
This is most likely the proper path on OS X.

Now run `make`. An executable called `exos.efi` should now be in your working directory.


### Testing

Required for testing are `qemu`, which is obtainable via homebrew or equivalent,
and the UEFI firmware for Qemu, `OVMF.fd`, available here: http://tianocore.sourceforge.net/wiki/OVMF.

Now run `make run`.

### Debugging

Install `gdb` to debug with Qemu.
Run `make run-debug` to start Qemu with debug options.
Startet this way, Qemu will stop at startup and listen for a gdb instance.
Start gdb in another shell, run 'target remote 127.0.0.1' and type 'c' to let Qemu continue to boot.
