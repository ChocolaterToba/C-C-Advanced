cmake_minimum_required(VERSION 2.8)

project(DZ1)

set(CMAKE_CXX_STANDARD 11)

#----------------------------------------------------------------------------
# Define project sources and includes
#----------------------------------------------------------------------------
set(COMMON_INCLUDES include)
include_directories(${COMMON_INCLUDES})
file(GLOB SRC_FILES src/*.c)
file(GLOB TEST_SRC_FILES test/*.cpp)
list(REMOVE_ITEM SRC_FILES src/main.c)

################################
# Normal Libraries
################################
add_library(DZ1_lib ${SRC_FILES})

################################
# Main Project
################################
add_executable(DZ1 src/main.c)
target_link_libraries(DZ1 DZ1_lib)

################################
# Testing
################################

# Options. Turn on with 'cmake -Dmyvarname=ON'.
#                       'cmake -TESTING=ON'.
option(TESTING "Build all tests." OFF) # Makes boolean 'test' available.

if (TESTING)
  # Locate GTest
  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})

  enable_testing()
 
  # Link runTests with what we want to test and the GTest and DZ1 library
  add_executable(runTests ${TEST_SRC_FILES})
  target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
  target_link_libraries(runTests DZ1_lib)

  gtest_discover_tests(runTests)

  set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/.travis/cmake)

endif ()
