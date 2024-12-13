cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME Echec)

project(${PROJECT_NAME} 
        VERSION 1.0
        LANGUAGES CXX
)

if(QT_VERSION VERSION_LESS 6.3)
    macro(qt_standard_project_setup)
        set(CMAKE_AUTOMOC ON)
        set(CMAKE_AUTORCC ON)
        set(CMAKE_AUTOUIC ON)
    endmacro()
endif()

if(QT_VERSION VERSION_LESS 6.0)
    macro(qt_add_executable name)
        if(ANDROID)
            add_library(name SHARED ${ARGN})
        else()
            add_executable(${ARGV})
        endif()
    endmacro()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/MP)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/output/Release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/output/Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/output/Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/output/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/output/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/output/Debug)

add_compile_definitions(QT_DISABLE_DEPRECATED_UP_TO=0x060000)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)

qt_standard_project_setup()

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/gui
)

# Define a function to group files
function(group_files BASE_DIR)
    file(GLOB_RECURSE ALL_FILES "${BASE_DIR}/*.*")
    foreach(FILE ${ALL_FILES})
        file(RELATIVE_PATH REL_PATH ${CMAKE_SOURCE_DIR} ${FILE})
        get_filename_component(FILE_PATH ${REL_PATH} PATH)
        string(REPLACE "/" "\\" GROUP_PATH ${FILE_PATH})
        source_group(${GROUP_PATH} FILES ${FILE})
    endforeach()
endfunction()

# Group all source files
group_files("${CMAKE_CURRENT_SOURCE_DIR}")

# Collect source, header, and UI files
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hxx"
)

file(GLOB_RECURSE UI_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
)

qt_wrap_ui(UI_HEADERS ${UI_FILES})

qt_add_executable(${PROJECT_NAME} 
        ${SOURCES} 
        ${HEADERS} 
        ${UI_HEADERS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
