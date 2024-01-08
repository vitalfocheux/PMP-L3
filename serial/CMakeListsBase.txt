cmake_minimum_required(VERSION 3.10)

project(Serial
  LANGUAGES CXX
)

find_package(Threads)
include(CTest)

# Compile googltest as static lib
add_library(googletest1 STATIC
  googletest/googletest/src/gtest-all.cc
)

target_compile_features(googletest1
  PUBLIC
    cxx_std_17
)

target_compile_options(googletest1
  PRIVATE
    "-g" "-O2"
)

target_include_directories(googletest1
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
)

add_executable(testSerial
  Serial.cc
  testSerial.cc
)

target_include_directories(testSerial
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
)

target_compile_options(testSerial
  PRIVATE
  "-Wall" "-Wextra" "-g" "-fsanitize=address,undefined"
)

target_compile_features(testSerial
  PUBLIC
    cxx_std_17
)

set_target_properties(testSerial
  PROPERTIES
    CXX_EXTENSIONS OFF
    LINK_FLAGS "-fsanitize=address,undefined"
)

target_link_libraries(testSerial
  PRIVATE
    googletest1
    Threads::Threads
)

include(GoogleTest)
gtest_discover_tests(testSerial)
