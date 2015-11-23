cmake_minimum_required( VERSION 3.0.2 )

#project name
project( Network )

#find packages
find_package( Qt5Core       REQUIRED )
find_package( Qt5Network    REQUIRED )

set( ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}" )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${ROOT_DIR}/cmake/" )
set( CONFIG_PATH "${ROOT_DIR}/config.in" )
set( CONFIG_TEMPLATE_PATH "${ROOT_DIR}/cmake/templates/config.in" )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )
set( CMAKE_CXX_STANDARD 11 )

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#include section
include( custom-tools )
include( cotire )

#set build path
foreach( OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUT_CONFIG} OUTPUT_CONFIG )
    set_target_properties( ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${OUTPUT_DIR} )
endforeach( OUTPUT_CONFIG CMAKE_CONFIGURATION_TYPES )
SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin )
SET( LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin )

#settings
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC OFF )

#message( "Qt found at: \"${QT5_PATH}\"" )
set( CMAKE_PREFIX_PATH ${QT5_PATH} )

include_directories( "${ROOT_DIR}" )
include_directories( "${CMAKE_CURRENT_LIST_DIR}" )
include_directories( "${QT5_PATH}/include" )

add_definitions(
    -D_CRT_SECURE_NO_DEPRECATE
)

#build file list
file( GLOB_RECURSE H_FILES "${CMAKE_CURRENT_LIST_DIR}/*.h" )
file( GLOB_RECURSE CPP_FILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp" )

set( USER_FILES ${H_FILES} ${CPP_FILES} )

qt5_wrap_cpp( MOC_LIST ${H_FILES} )
set( GENERATED_FILES ${MOC_LIST} )

set( ALL_FILES ${USER_FILES} ${GENERATED_FILES} )

apply_source_groups( USER_FILES ${CMAKE_CURRENT_LIST_DIR} "Sources" )
apply_source_groups( GENERATED_FILES ${CMAKE_CURRENT_BINARY_DIR} "Generated" )

add_subdirectory( Common )

#compiling
add_library( ${PROJECT_NAME} SHARED  ${ALL_FILES} )

#linking
target_link_libraries( ${PROJECT_NAME} Qt5::Core )
target_link_libraries( ${PROJECT_NAME} Qt5::Network )
target_link_libraries( ${PROJECT_NAME} Common )

#cotire
set_target_properties( ${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "Common.h" )
cotire( ${PROJECT_NAME} )
