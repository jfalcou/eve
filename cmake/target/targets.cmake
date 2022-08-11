##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup our tests main tests targets
##==================================================================================================
add_custom_target(tests)
add_custom_target(unit)
add_custom_target(html)
add_dependencies(tests unit)

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.exe              )
add_custom_target(unit.scalar.exe       )
add_custom_target(unit.basic.exe        )
add_custom_target(unit.simd.exe         )
add_custom_target(random.exe            )
add_custom_target(random.scalar.exe     )
add_custom_target(random.simd.exe       )
add_custom_target(exhaustive.exe        )
add_custom_target(exhaustive.scalar.exe )
add_custom_target(exhaustive.simd.exe   )

add_dependencies(unit.exe       doc.exe                  )
add_dependencies(unit.exe       unit.scalar.exe          )
add_dependencies(unit.exe       unit.simd.exe            )
add_dependencies(random.exe     random.scalar.exe        )
add_dependencies(random.exe     random.simd.exe          )
add_dependencies(exhaustive.exe exhaustive.scalar.exe    )
add_dependencies(exhaustive.exe exhaustive.simd.exe      )

add_dependencies(unit.basic.exe unit.arch.exe   )
add_dependencies(unit.basic.exe unit.api.exe    )
add_dependencies(unit.basic.exe unit.meta.exe   )
