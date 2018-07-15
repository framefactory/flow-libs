# ------------------------------------------------------------------------------
# Flow Libraries - glTF
# ------------------------------------------------------------------------------

# Automatically create a list of source files
file(GLOB SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Automatically create a list of header files
file(GLOB HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

set(AllFiles "${SourceFiles};${HeaderFiles}")
source_group("All Files" FILES ${AllFiles})

# ------------------------------------------------------------------------------
# BUILD TARGET

add_library(FlowGLTF STATIC ${AllFiles})
add_definitions(-DF_GLTF_LIB)
set_property(TARGET FlowGLTF PROPERTY FOLDER "_libs")

# ------------------------------------------------------------------------------
# INSTALL TARGET

# Nothing to do
