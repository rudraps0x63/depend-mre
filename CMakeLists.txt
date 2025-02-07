cmake_minimum_required(VERSION 3.25)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)

project(addon_a LANGUAGES CXX C)

add_bare_module(addon_a EXPORTS)

target_sources(
  ${addon_a}
  PRIVATE
    binding.cc
)

if(WIN32)
  target_link_libraries(
    ${addon_a}
    PRIVATE
      msvcrt.lib
  )
endif()
