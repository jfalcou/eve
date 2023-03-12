##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================
set(unit_root "${PROJECT_SOURCE_DIR}/test/unit")
set(module_root "${PROJECT_SOURCE_DIR}/test/unit/module")

##==================================================================================================
## GLOB and process arch unit tests
##==================================================================================================
add_custom_target(unit.api.exe         )
add_dependencies(unit.exe unit.api.exe )
glob_unit("unit" ${unit_root} "api/regular/*.cpp")
glob_unit("unit" ${unit_root} "api/regular/shuffle/*.cpp")
glob_unit("unit" ${unit_root} "api/regular/swizzle/*.cpp")
glob_unit("unit" ${unit_root} "api/tuple/*.cpp")
glob_unit("unit" ${unit_root} "api/tuple/algorithm/*.cpp")
glob_unit("unit" ${unit_root} "api/tuple/constant/*.cpp")
glob_unit("unit" ${unit_root} "api/tuple/shuffle/*.cpp")
glob_unit("unit" ${unit_root} "api/tuple/swizzle/*.cpp")
glob_unit("unit" ${unit_root} "api/udt/*.cpp")

##==================================================================================================
## GLOB and process arch unit tests
##==================================================================================================
add_custom_target(unit.arch.exe         )
add_dependencies(unit.exe unit.arch.exe )
glob_unit("unit" ${unit_root} "arch/*.cpp")

##==================================================================================================
## GLOB and process internals unit tests
##==================================================================================================
add_custom_target(unit.internals.exe         )
add_dependencies(unit.exe unit.internals.exe )
glob_unit("unit" ${unit_root} "internals/*.cpp")

##==================================================================================================
## GLOB and process memory unit tests
##==================================================================================================
add_custom_target(unit.memory.exe         )
add_dependencies(unit.exe unit.memory.exe )
glob_unit("unit" ${unit_root} "memory/*.cpp"               )
glob_unit("unit" ${unit_root} "memory/load/*.cpp"          )
glob_unit("unit" ${unit_root} "memory/store/*.cpp"         )
glob_unit("unit" ${unit_root} "memory/compress_store/*.cpp")

##==================================================================================================
## GLOB and process meta unit tests
##==================================================================================================
add_custom_target(unit.meta.exe         )
add_dependencies(unit.exe unit.meta.exe )
glob_unit("unit" ${unit_root} "meta/*.cpp"         )
glob_unit("unit" ${unit_root} "meta/concepts/*.cpp")
glob_unit("unit" ${unit_root} "meta/traits/*.cpp"  )

##==================================================================================================
## GLOB and process meta unit tests
##==================================================================================================
add_custom_target(unit.regression.exe         )
add_dependencies(unit.exe unit.regression.exe )
glob_unit("unit" ${unit_root} "regression/*.cpp" )

##==================================================================================================
## GLOB and process modules unit tests
##==================================================================================================
add_custom_target(unit.algo.exe         )
add_dependencies(unit.exe unit.algo.exe )
glob_unit("unit" ${unit_root} "module/algo/*.cpp"          )
glob_unit("unit" ${unit_root} "module/algo/algorithm/*.cpp")
glob_unit("unit" ${unit_root} "module/algo/container/*.cpp")
glob_unit("unit" ${unit_root} "module/algo/views/*.cpp"    )

add_custom_target(unit.core.exe         )
add_dependencies(unit.exe unit.core.exe )
glob_unit("unit" ${unit_root} "module/core/*.cpp"          )
glob_unit("unit" ${unit_root} "module/core/convert/*.cpp"  )
glob_unit("unit" ${unit_root} "module/core/saturate/*.cpp" )

add_custom_target(unit.combinatorial.exe         )
add_dependencies(unit.exe unit.combinatorial.exe )
glob_unit("unit" ${unit_root} "module/combinatorial/*.cpp" )

if(EVE_USE_BOOST)
add_custom_target(unit.bessel.exe         )
add_dependencies(unit.exe unit.bessel.exe )
glob_unit("unit" ${unit_root} "module/bessel/*.cpp" )

add_custom_target(unit.complex.exe         )
add_dependencies(unit.exe unit.complex.exe )
glob_unit("unit" ${unit_root} "module/complex/*.cpp" )

if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "powerpc")
add_custom_target(unit.doublereal.exe         )
add_dependencies(unit.exe unit.doublereal.exe )
glob_unit("unit" ${unit_root} "module/doublereal/*.cpp" )
glob_unit("unit" ${unit_root} "module/doublereal/core/*.cpp" )
glob_unit("unit" ${unit_root} "module/doublereal/math/*.cpp" )
glob_unit("unit" ${unit_root} "module/doublereal/constants/*.cpp" )
endif()

add_custom_target(unit.elliptic.exe         )
add_dependencies(unit.exe unit.elliptic.exe )
glob_unit("unit" ${unit_root} "module/elliptic/*.cpp" )

add_custom_target(unit.math.exe         )
add_dependencies(unit.exe unit.math.exe )
glob_unit("unit" ${unit_root} "module/math/*.cpp" )

add_custom_target(unit.polynomial.exe         )
add_dependencies(unit.exe unit.polynomial.exe )
glob_unit("unit" ${unit_root} "module/polynomial/*.cpp" )

add_custom_target(unit.special.exe         )
add_dependencies(unit.exe unit.special.exe )
glob_unit("unit" ${unit_root} "module/special/*.cpp" )

endif()
