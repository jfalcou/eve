##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.api.exe          )
add_custom_target(unit.api.regular.exe  )
add_custom_target(unit.api.tuple.exe    )
add_custom_target(unit.api.simd.exe     )

add_dependencies(unit.simd.exe      unit.api.simd.exe     )
add_dependencies(unit.api.exe       unit.api.simd.exe     )
add_dependencies(unit.api.simd.exe  unit.api.regular.exe  )
add_dependencies(unit.api.simd.exe  unit.api.tuple.exe    )

add_subdirectory(regular)
add_subdirectory(tuple)
add_subdirectory(udt)
