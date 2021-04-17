##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.real.polynomial.exe       )
add_custom_target(unit.real.polynomial.scalar.exe)
add_custom_target(unit.real.polynomial.simd.exe  )

add_dependencies(unit.real.scalar.exe      unit.real.polynomial.scalar.exe )
add_dependencies(unit.real.simd.exe        unit.real.polynomial.simd.exe   )
add_dependencies(unit.real.polynomial.exe  unit.real.polynomial.scalar.exe )
add_dependencies(unit.real.polynomial.exe  unit.real.polynomial.simd.exe   )

##==================================================================================================
## new style tests
##==================================================================================================
make_unit("unit.real.polynomial"           gegenbauer.cpp                  )
make_unit("unit.real.polynomial"           hermite.cpp                     )
make_unit("unit.real.polynomial"           horner.cpp                      )
make_unit("unit.real.polynomial"           legendre.cpp                    )
make_unit("unit.real.polynomial"           laguerre.cpp                    )
make_unit("unit.real.polynomial"           newton.cpp                      )
