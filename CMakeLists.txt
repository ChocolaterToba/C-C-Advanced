cmake_minimum_required(VERSION 3.10)



set(PROJECT_NAME DZ1)
project(${PROJECT_NAME})

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
add_library(${PROJECT_NAME}_lib ${SRC_FILES})

################################
# Main Project
################################
add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

################################
# Testing
################################

# Options. Turn on with 'cmake -Dmyvarname=ON'.
#                       'cmake -TESTING=ON'.
option(TESTING "Build all tests." OFF) # Makes boolean 'test' available.

if (TESTING)
  # Install Gtest
  ############################################
  # Download and unpack googletest at configure time
  configure_file(test/CMakeLists.txt.in googletest-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()

  # Prevent overriding the parent project's compiler/linker
  # settings on Windows
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  # Add googletest directly to our build. This defines
  # the gtest and gtest_main targets.
  add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                   ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                   EXCLUDE_FROM_ALL)

  # The gtest/gtest_main targets carry header search path
  # dependencies automatically when using CMake 2.8.11 or
  # later. Otherwise we have to add them here ourselves.
  if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
  endif()
  ########################

  enable_testing()
 
  # Link runTests with what we want to test and the GTest and DZ1 library
  add_executable(runTests ${TEST_SRC_FILES})
  target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
  target_link_libraries(runTests ${PROJECT_NAME}_lib)

  gtest_discover_tests(runTests)

  set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/.travis/cmake)

endif ()
