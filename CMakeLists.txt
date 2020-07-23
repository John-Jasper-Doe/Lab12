# Root CMake file for BULK SERVER Project
#
# Copyright John Doe 2020
# Distributed under the OSI-approved BSD 3-Clause License. See accompanying
# file LICENSE.txt or https://opensource.org/licenses/BSD-3-Clause for details.

cmake_minimum_required(VERSION 3.8)

# Setting name for this project.
set(PROJECT_NAME bulk_server)
set(PROJECT_DESCRIPTION "Library of bulk server")

# Adding a path with "cmake" modules to the system search paths.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Setting up a project version.
include(version)
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
  set(BLK_SRV_PATCH $ENV{TRAVIS_BUILD_NUMBER})
endif ()
set(BLK_SRV_VERSION ${BLK_SRV_MAJOR}.${BLK_SRV_MINOR}.${BLK_SRV_PATCH})
set(PROJECT_VERSION ${BLK_SRV_MAJOR}.${BLK_SRV_MINOR}.${BLK_SRV_PATCH})
configure_file(version.hpp.in ${CMAKE_BINARY_DIR}/src/include/version.hpp @ONLY)

## Set property
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -Wextra -Wpedantic -g -O0)

# Setting up a project.
include(print)
include(function)
include(GNUInstallDirs)

project(
  ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  DESCRIPTION ${PROJECT_DESCRIPTION}
  LANGUAGES CXX
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/lib/libasync/include)
include_directories(${LIBRARY_INCLUDE_PATH})

# Setting options on project
option(CLANG_FORMAT "Enable clang-format target" OFF)
option(DOCUMENTATION "Build documentation" ON)
option(TESTING "Build tests" ON)

if(CLANG_FORMAT)
  include(clang-format)
endif()

if(DOCUMENTATION)
  find_package(Doxygen COMPONENTS dot)
  include(doxygen)
endif()

# Settings for test cases.
if (TESTING)
  print("Target \"test\" enabled")
  include(gtest)
  # set GTEST_INCLUDE_DIR properly
  set(GTEST_INCLUDE_DIR
    ${CMAKE_SOURCE_DIR}/3rdpaty/gtest/src/googletest/include
    CACHE PATH "path to gtest includes"
  )
  include(CTest)
  include_directories(${GTEST_INCLUDE_DIR})
  add_subdirectory(test)
  enable_testing()
endif()

# Added directory
add_subdirectory(lib)
add_subdirectory(src)

configure_file(async.pc.in ${CMAKE_CURRENT_BINARY_DIR}/async.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/async.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# generate .deb package
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT john.jasper.doe@gmail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

# include will generate proper code for .deb generation
include(CPack)

