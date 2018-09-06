This is a library of C++ utility classes and functions.

It can be built using the makefiles in the makefiles/ directory.
For now, building is tested only for gcc and clang on Linux.
Both 32-bit and 64-bit builds are supported.

Directory overrides/ contains some slightly modified system include files,
where the identifier "uint" is commented out to avoid name conflicts.
If you have different versions of those files, you can change them
in a similar manner.

Files pvmhelp.cpp and pvmhelp.h are used for interfacing with the PVM3 library
(http://www.netlib.org/pvm3/). If you don't have that library,
you don't need them, and you can freely delete them.
