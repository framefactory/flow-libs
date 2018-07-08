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
# 3RD PARTY LIBRARIES

# Google Draco Mesh Compression
set(Draco_DIR "${PROJECT_SOURCE_DIR}/vendor/draco")
set(Draco_INCLUDE_DIR "${Draco_DIR}/include")
set(Draco_LIB_DEBUG "${Draco_DIR}/lib/Debug/draco.lib")
set(Draco_LIB_RELEASE "${Draco_DIR}/lib/Release/draco.lib")
message("Draco Directory: " ${Draco_DIR})

# ------------------------------------------------------------------------------
# BUILD TARGET

add_library(FlowGLTF STATIC ${AllFiles})
add_definitions(-DF_GLTF_LIB)
set_property(TARGET FlowGLTF PROPERTY FOLDER "_libs")

target_include_directories(FlowGLTF BEFORE PRIVATE
    ${Draco_INCLUDE_DIR}
)

target_link_libraries(FlowGLTF
    optimized ${Draco_LIB_RELEASE}
	debug ${Draco_LIB_DEBUG}
)


# ------------------------------------------------------------------------------
# INSTALL TARGET

# Nothing to do
