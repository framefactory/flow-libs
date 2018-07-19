# ------------------------------------------------------------------------------
# Flow Libs - glTF Test App
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
# 3RD PARTY LIBRARIES

#find_package(Qt5 COMPONENTS Core REQUIRED)
#find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# ------------------------------------------------------------------------------
# BUILD TARGET

add_executable(glTFTest ${AllFiles})
set_target_properties(glTFTest PROPERTIES DEBUG_POSTFIX "d")
set_property(TARGET glTFTest PROPERTY FOLDER "_apps")

target_include_directories(glTFTest BEFORE PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/source
#	Qt5::Core
#	Qt5::Gui
#	Qt5::Widgets
)

target_link_libraries(glTFTest
#    Qt5::Core
#    Qt5::Gui
#    Qt5::Widgets
    FlowCore
    FlowGLTF
)

