# CMakeLists.txt
# CMake build configuration
# 
# From seq64 - Sequenced music editor for first-party N64 games
# Copyright (C) 2014-2023 Sauraen
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.13)

set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "" FORCE)
set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)

project(SEQ64 VERSION 2.4.0)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/juce/CMakeLists.txt")
    message(FATAL_ERROR "You forgot to get the Git submodules, please run git submodule update --init")
endif()

# Version selection setup

option(SEQ64_CONSOLE_ONLY "Whether SEQ64 should build console version only" OFF)
option(SEQ64_BUILD_GUI "Whether SEQ64 should build console and GUI versions" OFF)

if(SEQ64_CONSOLE_ONLY)
    set(SEQ64_BUILD_GUI OFF CACHE BOOL "" FORCE)
elseif(NOT SEQ64_BUILD_GUI)
    if(WIN32 OR APPLE)
        set(SEQ64_BUILD_GUI ON)
    else()
        # On Linux and neither was set. Detect whether we are on a console-only
        # machine (i.e. WSL) by seeing if an X server is running or not.
        execute_process(COMMAND "xset" "q" TIMEOUT 0.5 OUTPUT_QUIET ERROR_QUIET 
            RESULT_VARIABLE result)
        if(result)
            # There was an error, so no GUI
            message(STATUS "Could not find X server, building console only")
            set(SEQ64_CONSOLE_ONLY TRUE)
        else()
            message(STATUS "Found X server, building GUI")
            set(SEQ64_BUILD_GUI TRUE)
        endif()
    endif()
endif()

# SEQ64 sources

add_subdirectory(Source)
list(TRANSFORM SEQ64_SHARED_SOURCES PREPEND "Source/")
list(TRANSFORM SEQ64_CONSOLE_ONLY_SOURCES PREPEND "Source/")
list(TRANSFORM SEQ64_GUI_ONLY_SOURCES PREPEND "Source/")

if(WIN32)
    set(SEQ64_COMPILE_OPTIONS "/W2" "/O2")
else()
    set(SEQ64_COMPILE_OPTIONS "-Wall" "-Wextra" "-Wno-sign-compare" "-Wno-sign-conversion" "-O2")
endif()

set(NAME_STR "SEQ64 V${PROJECT_VERSION}")
set(VER_STR "${PROJECT_VERSION}")
math(EXPR VER_HEX "${PROJECT_VERSION_MAJOR}*0x10000+${PROJECT_VERSION_MINOR}*0x100+${PROJECT_VERSION_PATCH}" OUTPUT_FORMAT HEXADECIMAL)
set(SEQ64_DEFINITIONS
    JUCE_STANDALONE_APPLICATION=1
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_APPLICATION_NAME_STRING="${NAME_STR}"
    JUCE_APPLICATION_VERSION_STRING="${VER_STR}"
    JUCE_APPLICATION_VERSION_HEX=${VER_HEX}
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

# Console version

add_executable(seq64_console
    ${SEQ64_SHARED_SOURCES}
    ${SEQ64_CONSOLE_ONLY_SOURCES}
    "juce/modules/juce_core/juce_core.cpp"
    "juce/modules/juce_events/juce_events.cpp"
    "juce/modules/juce_audio_basics/juce_audio_basics.cpp"
    "juce/modules/juce_data_structures/juce_data_structures.cpp"
)
target_include_directories(seq64_console PRIVATE
    "Source"
    "juce/modules"
)
target_compile_definitions(seq64_console PRIVATE
    ${SEQ64_DEFINITIONS}
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
    SEQ64_CONSOLE_ONLY=1
)
target_compile_options(seq64_console PRIVATE ${SEQ64_COMPILE_OPTIONS})
if(UNIX AND NOT APPLE)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(seq64_console Threads::Threads ${CMAKE_DL_LIBS})
endif()

# GUI version

if(SEQ64_BUILD_GUI)
    add_subdirectory(juce)
    
    juce_add_gui_app(seq64_gui PRODUCT_NAME "seq64_gui" COMPANY_NAME "Sauraen")
    juce_generate_juce_header(seq64_gui)
    target_sources(seq64_gui PRIVATE ${SEQ64_SHARED_SOURCES} ${SEQ64_GUI_ONLY_SOURCES})
    target_compile_definitions(seq64_gui PRIVATE
        ${SEQ64_DEFINITIONS}
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_MODAL_LOOPS_PERMITTED=1
    )
    target_link_libraries(seq64_gui PRIVATE
        juce::juce_core
        juce::juce_audio_basics
        juce::juce_data_structures
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
    )
    target_compile_options(seq64_gui PRIVATE ${SEQ64_COMPILE_OPTIONS})
endif()
