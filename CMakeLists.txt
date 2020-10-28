cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME DZ2)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

#----------------------------------------------------------------------------
# Define project sources and includes
#----------------------------------------------------------------------------
set(COMMON_INCLUDES include)
include_directories(${COMMON_INCLUDES})

file(GLOB SRC_FILES src/main.c src/process_input.c)

file(GLOB TEST_SRC_FILES test/main.cpp)

################################
# Static Single-Thread Library
################################
file(GLOB STATIC_LIB_FILES
     single_thread/src/single_thread.c
     single-thread/include/single_thread.h
)
add_library(${PROJECT_NAME}_static_lib STATIC ${STATIC_LIB_FILES})
target_include_directories(${PROJECT_NAME}_static_lib PUBLIC
                           ${PROJECT_SOURCE_DIR}/single_thread/include
)

################################
# Dynamic Multi-Thread Library
################################
file(GLOB DYNAMIC_LIB_FILES
     multi_thread/src/multi_thread.c
     multi_thread/include/multi_thread.h
)
add_library(${PROJECT_NAME}_dynamic_lib SHARED ${DYNAMIC_LIB_FILES})
target_include_directories(${PROJECT_NAME}_dynamic_lib PUBLIC
                           ${PROJECT_SOURCE_DIR}/multi_thread/include
)
target_link_libraries(${PROJECT_NAME}_dynamic_lib pthread)

################################
# Main Project
################################
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_static_lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_dynamic_lib)

################################
# Testing
################################

# Options. Turn on with 'cmake -Dmyvarname=ON'.
#                       'cmake -DENABLE_TESTING=ON'.
option(ENABLE_TESTING "Build all tests." OFF) # Makes boolean 'test' available.

if (ENABLE_TESTING)
  # Install Gtest
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.8.0
  )
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)

  include(CTest)
 
  # Link runTests with what we want to test and the GTest and DZ1 library
  add_executable(runTests ${TEST_SRC_FILES})
  target_link_libraries(runTests gtest_main pthread)
  target_link_libraries(runTests PRIVATE ${PROJECT_NAME}_static_lib)

  gtest_discover_tests(runTests)

endif()

option(ENABLE_COVERAGE "Run coverage" OFF)

if (ENABLE_COVERAGE)
  set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/coverage_module)
  include(CodeCoverage)

  if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(runTests gcov)
  endif()

  append_coverage_compiler_flags()
  setup_target_for_coverage_gcovr_html(
    NAME coverage
    EXECUTABLE runTests
    DEPENDENCIES ${PROJECT_NAME} runTests
    EXCLUDE "test/main.cpp" "build/_deps*" "src/main.c")
  
endif()