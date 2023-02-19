cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# Set C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Check for C++17 support
if(CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "ERROR: DynoCall, requires atleast a <= C++17 compatible compiler to build. Please make sure you have enabled C++ 17 support in your compiler flags. If C++ 17 support is already enabled and you are still encountering this error, please check that your CMakeLists.txt file is configured correctly. If you are unsure how to enable C++17 support in your compiler flags, please refer to your compiler's documentation.")
endif()

# Define FuncX Project
project(FuncX LANGUAGES CXX)

# Define the source files for our FuncX executable
set(EXECUTABLE_SOURCES "./src/dynocall.cpp")

# Define the source files for our FuncX DLL
set(DLL_SOURCES 
    "./src/dynocall_lib.cpp"
)

# Define the name for our executable
set(EXECUTABLE_NAME "DynoCall")

# Define the name for our DLL
set(DLL_NAME "DynoCallLib")

# Define the output directories for the DLL and Executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)


# Find Packages
find_package(fmt CONFIG REQUIRED)

if (NOT fmt_FOUND)
message(FATAL_ERROR "Formatting Library not Found.")
endif()

# Set Include Header Path
include_directories(
    C:/vcpkg/installed/${VCPKG_TARGET_TRIPLET}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Define the Executable target
add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})
    
# Define the DLL target
add_library(${DLL_NAME} SHARED ${DLL_SOURCES})
    
# Set the output name of the DLL
set_target_properties(${DLL_NAME} PROPERTIES OUTPUT_NAME ${DLL_NAME})
    
# Link Libraries
target_link_libraries(${EXECUTABLE_NAME} PRIVATE fmt::fmt-header-only)
target_link_libraries(${DLL_NAME} PRIVATE fmt::fmt-header-only)