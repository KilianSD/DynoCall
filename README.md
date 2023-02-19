# DynoCall
DynoCall is a simple program that facilitates learning C++, when learning C++ you will usually have to write many different files to test the language. This will usually result in you being disorganized and having a bunch of binaries that all achieve a really simple task. Instead you can write your code as header files and include them in the DLL main file (dynocall_lib.cpp) then from our executable we can call this function by providing to our executable as the first argument.

Example:
.\dynocall.exe back_inserter

The preceeding example will result in the function back_inserter from our DLL to be executed.