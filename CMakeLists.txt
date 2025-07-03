cmake_minimum_required(VERSION 3.20)
project(ollvm-pass)

option(BUILD_ANDROID_NDK "Build for Android NDK" OFF)

if(BUILD_ANDROID_NDK)
    message(STATUS "LLVM_DIR: ${LLVM_DIR}")
    set(CMAKE_C_COMPILER ${LLVM_DIR}/bin/clang)
    set(CMAKE_CXX_COMPILER ${LLVM_DIR}/bin/clang++)
    list(APPEND CMAKE_PREFIX_PATH "${LLVM_DIR}/lib/cmake/llvm")
else()
  set(LT_LLVM_INSTALL_DIR  "" CACHE PATH "/opt/homebrew/opt/llvm@19")
  # Add the location of LLVMConfig.cmake to CMake search paths (so that
  # find_package can locate it)
  list(APPEND CMAKE_PREFIX_PATH "${LT_LLVM_INSTALL_DIR}/lib/cmake/llvm/")
endif()

find_package(LLVM REQUIRED CONFIG)
if(BUILD_ANDROID_NDK)
else()
  if("${LLVM_VERSION_MAJOR}" VERSION_LESS 18)
    message(FATAL_ERROR "Found LLVM ${LLVM_VERSION_MAJOR}, but need LLVM 18 or above")
  endif()
endif()

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(AddLLVM)

if(BUILD_ANDROID_NDK)
  add_definitions(${LLVM_DEFINITIONS})
  include_directories(${LLVM_INCLUDE_DIRS})
  link_directories(${LLVM_LIBRARY_DIRS})
else()
  separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
  add_definitions(${LLVM_DEFINITIONS_LIST})
  include_directories(${LLVM_INCLUDE_DIRS})
endif()

#===============================================================================
# 2. LLVM-TUTOR BUILD CONFIGURATION
#===============================================================================
# Use the same C++ standard as LLVM does
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

add_subdirectory(obfuscation)
