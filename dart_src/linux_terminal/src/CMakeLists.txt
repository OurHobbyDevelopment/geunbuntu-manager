# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

project(linux_terminal_library VERSION 0.0.1 LANGUAGES CXX)

add_library(linux_terminal SHARED
  "linux_terminal.cpp"
)

set_target_properties(linux_terminal PROPERTIES
  PUBLIC_HEADER linux_terminal.h
  OUTPUT_NAME "linux_terminal"
)

target_compile_definitions(linux_terminal PUBLIC DART_SHARED_LIB)
