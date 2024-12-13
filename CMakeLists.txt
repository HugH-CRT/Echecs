cmake_minimum_required(VERSION 3.16)

project(Echec 
    VERSION 1.0 
    LANGUAGES CXX
)

add_subdirectory(source)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Echec)