cmake_minimum_required(VERSION 3.25)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(addon_b LANGUAGES CXX C)

add_bare_module(addon_b)

target_sources(
  ${addon_b}
  PRIVATE
    binding.cc
)

link_bare_module(${addon_b} a SHARED)
