# DynoCall
DynoCall is a simple program that facilitates the learning of C++. 

When learning C++ you will tend to write many different files to test the language. This will usually result in you being disorganized and having a bunch of binaries that all achieve a really simple task. 

Instead you can write your code in header files and include them in the DLL main file (dynocall_lib.cpp) then from our executable we can call this function by it to our executable as the first argument.

```
Example:
.\dynocall.exe back_inserter
```

The preceeding example will result in the function back_inserter from our DLL to be executed.

You can also provide arguments to a function.

```
Example:
.\dynocall.exe memory_injection 'CFF Explorer.exe'
```

The preceeding example will execute the function memory_injection from our DLL and will give the argument 'CFF Explorer' to our function, arguments are passed as `std::vector<void*>` and are casted back into their right type in the function you want to execute.

If you write a function that requires arguments, make sure you verify the user actually passed these arguments to the function else you can stop the execution of it.

# How to use
To use this program, you're gonna need to write your code as header files (.h) in the include directory, then you are going to include these header files in `src/dynocall_lib.cpp`, make sure you put the functions you want to export as `extern "C"` and put the `EXPORT` macro in your function definitions (`void* EXPORT myFunction(){};`).

Then you can compile the program with vscode `ctrl + shift + p` -> `CMAKE: configure` -> `ctrl + shift + p` -> `CMAKE: build release`, this will build the executable and the DLL in the bin folder.

Or you can compile the program manually with the following commands (note that you will need to provide your own paths for the toolchain file and the cmake prefix path) :
```
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_PREFIX_PATH=C:/vcpkg/installed/x64-windows
cmake --build . --config Release
```

You can then run your functions with `.\dynocall.exe myFunction argument1 argument2`, note that this project was principally made so that i can use it (not for the public), but the repository is still publicly available for whoever wants to use this or make something similar.

If you are having trouble understanding how to use the program, the DLL currently exports 2 functions, `back_inserter` and `memory injection`, those functions are declared inside the `back_inserter.h` and `memory_injection.h` file, you are free to look at those to see how it works.