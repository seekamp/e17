cmake_minimum_required(VERSION 2.6)
project(eobj)
set(EOBJ_VERSION_MAJOR 0)
set(EOBJ_VERSION_MINOR 1)
set(EOBJ_VERSION_MICRO 0)
set(EOBJ_VERSION ${EOBJ_VERSION_MAJOR}.${EOBJ_VERSION_MINOR}.${EOBJ_VERSION_MICRO})

set(PACKAGE ${CMAKE_PROJECT_NAME})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include_directories ("${PROJECT_BINARY_DIR}")

find_package(Eina REQUIRED)
find_package(Evas REQUIRED)
find_package(Elementary REQUIRED)

# likely put this into an FindCompilerAttribute.cmake:
INCLUDE(CheckCSourceCompiles)
SET(HAVE___ATTRIBUTE__)
CHECK_C_SOURCE_COMPILES(
   "void  foo (int bar __attribute__((unused)) ) { }
   static void baz (void) __attribute__((unused));
   static void baz (void) { }
   int main(){}
   " HAVE___ATTRIBUTE__
   )

ADD_DEFINITIONS(-DPACKAGE_BIN_DIR="${CMAKE_INSTALL_PREFIX}/bin"
   -DPACKAGE_DATA_DIR="${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}"
   -DPACKAGE_LIB_DIR="${CMAKE_INSTALL_PREFIX}/lib")

ADD_DEFINITIONS(-DHAVE_CONFIG_H)

configure_file (
   "${PROJECT_SOURCE_DIR}/cmakeconfig.h.in"
   "${PROJECT_BINARY_DIR}/config.h"
   )

include(EFLCheck)

add_subdirectory(lib)
add_subdirectory(examples/evas)
add_subdirectory(examples/mixin)
add_subdirectory(examples/signals)
add_subdirectory(examples/access)
add_subdirectory(examples/constructors)

add_subdirectory(tests EXCLUDE_FROM_ALL)
