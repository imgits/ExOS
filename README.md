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

Run `make`. An executable called `exos.efi` should now be in your working directory.  

If the build fails with an error message akin to "'header_name' file not found", you must  
find out the path to your C++ system headers and export them:  
`export CPLUS_INCLUDE_PATH=YOUR_PATH_HERE`.  
Then try again.

### Testing

Required for testing are `qemu`, which is obtainable via homebrew or equivalent,
and the UEFI firmware for Qemu, `OVMF.fd`, available here: http://tianocore.sourceforge.net/wiki/OVMF.

Now run `make run`.

### Debugging

Install `gdb` to debug with Qemu.
Run `make run-debug` to start Qemu with debug options.
Startet this way, Qemu will stop at startup and listen for a gdb instance.
Start gdb in another shell, run 'target remote 127.0.0.1' and type 'c' to let Qemu continue to boot.
