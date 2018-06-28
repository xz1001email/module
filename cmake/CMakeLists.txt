
cmake_minimum_required (VERSION 2.6)
project (Tutorial)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# should we use our own math functions?
option (USE_MYMATH "Use tutorial provided math implementation" OFF)
#option (USE_MYMATH "Use tutorial provided math implementation" ON)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
    "${PROJECT_BINARY_DIR}/TutorialConfig.h"
    )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# add the MathFunctions library?
if (USE_MYMATH)
    message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
    message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
    MESSAGE(STATUS “HOME dir: $ENV{HOME}”)
    include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
    #增加一个子目录单独编译。
    add_subdirectory (MathFunctions)
    set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# add the executable
add_executable (Tutorial tutorial.cpp)
target_link_libraries (Tutorial  ${EXTRA_LIBS})

