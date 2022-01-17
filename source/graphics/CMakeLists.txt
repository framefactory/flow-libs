# ------------------------------------------------------------------------------
# Flow Libraries - Graphics
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

add_library(FlowGraphics STATIC ${AllFiles})
add_definitions(-DF_GRAPHICS_LIB)
set_property(TARGET FlowGraphics PROPERTY FOLDER "_libs")

# compiler flags
target_compile_features(FloGraphics PRIVATE cxx_std_11)

# ------------------------------------------------------------------------------
# INSTALL TARGET

# Nothing to do
