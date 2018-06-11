## -------------------------------------------------------------------------------------------------
##                              Copyright 2018 Joel FALCOU
##
##            Adapted from https://github.com/Crascit/DownloadProject/blob/master/CMakeLists.txt
##
##                   Distributed under the Boost Software License, Version 1.0.
##                        See accompanying file LICENSE.txt or copy at
##                            http://www.boost.org/LICENSE_1_0.txt
## -------------------------------------------------------------------------------------------------

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
