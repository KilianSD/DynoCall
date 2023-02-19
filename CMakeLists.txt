cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# Set C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Check for C++17 support
if(CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "ERROR: DynoCall, requires atleast a <= C++17 compatible compiler to build. Please make sure you have enabled C++ 17 support in your compiler flags. If C++ 17 support is already enabled and you are still encountering this error, please check that your CMakeLists.txt file is configured correctly. If you are unsure how to enable C++17 support in your compiler flags, please refer to your compiler's documentation.")
endif()

# Set the vcpkg directory path
set(VCPKG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")
set(VCPKG_EXE "${VCPKG_DIR}/vcpkg.exe")

# Check OS for archive decompression Command
if(WIN32)
    set(UNZIP_COMMAND "unzip")
elseif(UNIX)
    set(UNZIP_COMMAND "tar -zxf")
endif()

# Check if the VCPKG directory exists
if(NOT EXISTS ${VCPKG_DIR})
    # If the VCPKG directory does not exist, download and install vcpkg
    message(STATUS "vcpkg not found, installing...")
    if(NOT EXISTS "${VCPKG_DIR}.zip")
        message(STATUS "vcpkg archive not found, downloading and extracting...")
        file(DOWNLOAD "https://github.com/microsoft/vcpkg/archive/master.zip" "${VCPKG_DIR}.zip")
    else()
        message(STATUS "vcpkg archive found, extracting...")
    endif()
    
    if(NOT EXISTS "${VCPKG_DIR}-master")
        if(WIN32)
            execute_process(COMMAND ${UNZIP_COMMAND} "${VCPKG_DIR}.zip" -q -d "${CMAKE_CURRENT_SOURCE_DIR}" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        elseif(UNIX)
            execute_process(COMMAND ${UNZIP_COMMAND} "${VCPKG_DIR}.zip" -q -C "${CMAKE_CURRENT_SOURCE_DIR}" WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        endif()
    endif()

    file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg-master ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg)

    execute_process(COMMAND "${VCPKG_DIR}/bootstrap-vcpkg.bat")
    execute_process(COMMAND ${VCPKG_DIR}/vcpkg.exe integrate install)
    endif()
    
    # Set the vcpkg toolchain file
    set(VCPKG_TOOLCHAIN_FILE "${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
    
    # Tell CMake to use the vcpkg toolchain file
    set(CMAKE_TOOLCHAIN_FILE ${VCPKG_TOOLCHAIN_FILE})
    set(CMAKE_PREFIX_PATH "${VCPKG_DIR}/installed/x64-windows")
    
    # Find Packages
    find_package(fmt CONFIG)
    
    if (NOT fmt_FOUND)
        message("formatting Library not found, installing...")
        execute_process(COMMAND ${VCPKG_DIR}/vcpkg.exe install fmt:x64-windows RESULT_VARIABLE result)
    
        if(result)
            message(FATAL_ERROR "failed to install formatting library !")
        else()
            find_package(fmt CONFIG REQUIRED)
        endif()
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




# Set Include Header Path
include_directories(
    ${VCPKG_DIR}/installed/${VCPKG_TARGET_TRIPLET}/include
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