##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
file(GLOB_RECURSE sources RELATIVE ${EVE_ROOT}
     ${EVE_ROOT}/include/*.hpp
     ${EVE_ROOT}/test/*.hpp ${EVE_ROOT}/test/*.cpp
     ${EVE_ROOT}/benchmarks/*.hpp ${EVE_ROOT}/benchmarks/*.cpp
     ${EVE_ROOT}/examples/*.hpp ${EVE_ROOT}/examples/*.cpp
    )
list(FILTER sources EXCLUDE REGEX "^include/eve/arch(/|\\.hpp$)")

set(offenders "")
foreach(source ${sources})
  file(STRINGS ${EVE_ROOT}/${source} lines REGEX "^[ \t]*#[ \t]*include[ \t]*[<\"]eve/arch/")
  if(lines)
    list(APPEND offenders ${source})
  endif()
endforeach()

if(offenders)
  list(JOIN offenders "\n  " offenders)
  message(FATAL_ERROR "Include eve/arch.hpp instead of eve/arch/ headers in:\n  ${offenders}")
endif()
