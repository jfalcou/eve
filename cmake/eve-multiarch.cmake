##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Tools for multi-arch compilation
##==================================================================================================
function(eve_build_support)
  set(_opts)
  set(_single_opts NAME    INTERFACE TARGET)
  set(_multi_opts  OPTIONS SOURCES)
  cmake_parse_arguments(_args "${_opts}" "${_single_opts}" "${_multi_opts}" ${ARGN})

  if(NOT DEFINED _args_NAME)
    message(FATAL_ERROR "[EVE] Missing component name")
  endif()
  if(NOT DEFINED _args_TARGET)
    message(FATAL_ERROR "[EVE] Missing target identifier")
  endif()
  if(NOT DEFINED _args_OPTIONS)
    message(FATAL_ERROR "[EVE] Missing architecture compiler-specific options")
  endif()
  if(NOT DEFINED _args_SOURCES)
    message(FATAL_ERROR "[EVE] No Source files provided")
  endif()

  add_library( ${_args_NAME}_${_args_TARGET} SHARED ${_args_SOURCES})
  target_link_libraries( ${_args_NAME}_${_args_TARGET} PRIVATE ${_args_INTERFACE})
  target_compile_options( ${_args_NAME}_${_args_TARGET} PUBLIC ${_args_OPTIONS})
endfunction()

function(eve_build_variants)
  set(_opts QUIET)
  set(_single_opts NAME   INTERFACE )
  set(_multi_opts  TARGET OPTIONS SOURCES)
  cmake_parse_arguments(_args "${_opts}" "${_single_opts}" "${_multi_opts}" ${ARGN})

  if(NOT DEFINED _args_NAME)
    message(FATAL_ERROR "[EVE] Missing component name")
  endif()

  foreach(tgt opt IN ZIP_LISTS _args_TARGET _args_OPTIONS)
    if(NOT _args_QUIET)
      message(STATUS "[EVE] Configuring target '${_args_NAME}' on for ${tgt} with '${opt}'")
    endif()

    eve_build_support(NAME "${_args_NAME}" INTERFACE "${_args_INTERFACE}" TARGET ${tgt} OPTIONS "${opt}" SOURCES ${_args_SOURCES})
  endforeach()
endfunction()
