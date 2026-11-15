##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
file(GLOB_RECURSE headers RELATIVE ${EVE_INCLUDE} ${EVE_INCLUDE}/eve/*.hpp)
list(FILTER headers EXCLUDE REGEX "^eve/deps/")

set(offenders "")
foreach(header ${headers})
  file(STRINGS ${EVE_INCLUDE}/${header} lines REGEX "^[ \t]*namespace[ \t]+eve([ \t{:]|$)")
  file(READ ${EVE_INCLUDE}/${header} content)
  set(independent FALSE)
  if(content MATCHES "(^|\n)EVE_ABI_INDEPENDENT_NAMESPACE\n{\n(([^}\n][^\n]*)?\n)*[ \t]*namespace[ \t]")
    set(independent TRUE)
  endif()
  if(lines OR independent)
    list(APPEND offenders ${header})
  endif()
endforeach()

if(offenders)
  list(JOIN offenders "\n  " offenders)
  message(FATAL_ERROR "Use EVE_NAMESPACE or EVE_ABI_INDEPENDENT_NAMESPACE instead of namespace eve in:\n  ${offenders}")
endif()
