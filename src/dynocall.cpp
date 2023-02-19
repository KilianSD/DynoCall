#include <iostream>
#include <vector>
#include <Windows.h>
#include <fmt/core.h>
#include <fmt/color.h>


typedef void (*FuncxType)(std::vector<void*>);

int main(int argc, char* argv[]){
    if(argc < 2){
        fmt::print(fg(fmt::color::red) | fmt::emphasis::bold,
            "Usage: {} <function> [<arg1> <arg2> ...]\n", argv[0]);
        return 1;
    }
    
    fmt::print(fg(fmt::color::lime) | fmt::emphasis::bold,
        "Executing function '{}'...\n", argv[1]);

    const char* libName = "DynoCallLib.dll";
    const char* funcName = argv[1];

    HINSTANCE hLib = LoadLibraryA(libName);
    if(!hLib){
        std::cerr << "Error: could not load library '" << libName << "'" << std::endl;
        return 1;
    }

    FuncxType funcx = (FuncxType)GetProcAddress(hLib, funcName);
    if(!funcx){
        std::cerr << "Error: could not find function '" << funcName << "' in library '" << libName << "'" << std::endl;
        return 1;
    }

    std::vector<void*> args;
    if(argc > 2){
        for(int i = 2; i < argc; i++){
            std::cout << argv[i] << std::endl;
            args.push_back((void*)argv[i]);
        }
    }

    funcx(args);

    FreeLibrary(hLib);
    return 0;
}