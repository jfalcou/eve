##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

function(add_parent_target target)
  string(REGEX REPLACE "[^.]+\\.([^.]+)$" "\\1" parent_target ${target})
  string(REGEX REPLACE "^.*\\.([^.]+)$" "\\1" suffix ${parent_target})

  if(NOT TARGET ${target})
    add_custom_target(${target})
    set_property(TARGET ${target} PROPERTY FOLDER ${suffix})
  endif()

  if(NOT ${parent_target} STREQUAL ${target})
    add_parent_target(${parent_target})
    add_dependencies(${parent_target} ${target})
  endif()
endfunction()
