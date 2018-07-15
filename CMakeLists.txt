cmake_minimum_required(VERSION 3.9.0)

# ------------------------------------------------------------------------------
# MAIN PROJECT

project(FlowLibs VERSION 0.1)
enable_language(CXX)

# ------------------------------------------------------------------------------
# GLOBAL SETTINGS

#Compiler flags
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -msse4")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W2")
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# Output directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release)

# Append "d" to all debug libraries
set(CMAKE_DEBUG_POSTFIX "d")

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# GUI_TYPE can be added to add_executable to indicate a GUI application
# this prevents the console to be shown on windows
if(WIN32)
  set(GUI_TYPE WIN32)
endif()

if(APPLE)
  set(GUI_TYPE MACOSX_BUNDLE)
endif()

# ------------------------------------------------------------------------------
# CHILD PROJECTS

# Add base include path for all libraries
include_directories(${PROJECT_SOURCE_DIR}/source)

# Add library components
add_subdirectory(source/core)
add_subdirectory(source/math)
add_subdirectory(source/gltf)
#add_subdirectory(source/graphics)

# Tests and test applications
add_subdirectory(source/tests/gltf)
add_subdirectory(source/tests/cpp)
