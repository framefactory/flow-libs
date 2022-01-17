# ------------------------------------------------------------------------------
# Flow Libs - CPP Test App
# ------------------------------------------------------------------------------

# Automatically create a list of source files
file(GLOB SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Automatically create a list of header files
file(GLOB HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

set(AllFiles ${SourceFiles};${HeaderFiles})
source_group("All Files" FILES ${AllFiles})

# ------------------------------------------------------------------------------
# BUILD TARGET

add_executable(CPPTest ${AllFiles})
set_target_properties(CPPTest PROPERTIES DEBUG_POSTFIX "d")
set_property(TARGET CPPTest PROPERTY FOLDER "_apps")

# compiler flags
target_compile_features(CPPTest PRIVATE cxx_std_11)

target_include_directories(CPPTest BEFORE PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/source
)

target_link_libraries(CPPTest
    FlowCore
    FlowGLTF
)

