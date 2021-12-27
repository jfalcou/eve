##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.ieee.exe                      )


##==================================================================================================
## new style tests
##==================================================================================================
make_unit("unit.ieee" exponent.cpp                )
make_unit("unit.ieee" frexp.cpp                   )
#make_unit("unit.ieee" ifrexp.cpp                  )
make_unit("unit.ieee" is_denormal.cpp             )
make_unit("unit.ieee" is_finite.cpp               )
make_unit("unit.ieee" is_flint.cpp                )
make_unit("unit.ieee" is_imag.cpp                 )
make_unit("unit.ieee" is_lessgreater.cpp          )
make_unit("unit.ieee" is_nan.cpp                  )
make_unit("unit.ieee" is_negative.cpp             )
make_unit("unit.ieee" is_ngez.cpp                 )
make_unit("unit.ieee" is_ngtz.cpp                 )
make_unit("unit.ieee" is_nlez.cpp                 )
make_unit("unit.ieee" is_nltz.cpp                 )
make_unit("unit.ieee" is_normal.cpp               )
make_unit("unit.ieee" is_not_denormal.cpp         )
make_unit("unit.ieee" is_not_finite.cpp           )
make_unit("unit.ieee" is_not_flint.cpp            )
make_unit("unit.ieee" is_not_greater_equal.cpp    )
make_unit("unit.ieee" is_not_greater.cpp          )
make_unit("unit.ieee" is_not_imag.cpp             )
make_unit("unit.ieee" is_not_infinite.cpp         )
make_unit("unit.ieee" is_not_less_equal.cpp       )
make_unit("unit.ieee" is_not_less.cpp             )
make_unit("unit.ieee" is_not_nan.cpp              )
make_unit("unit.ieee" is_not_real.cpp             )
make_unit("unit.ieee" is_ordered.cpp              )
make_unit("unit.ieee" is_positive.cpp             )
make_unit("unit.ieee" is_real.cpp                 )
make_unit("unit.ieee" is_unordered.cpp            )
make_unit("unit.ieee" ldexp.cpp                   )
make_unit("unit.ieee" mantissa.cpp                )
make_unit("unit.ieee" nextafter.cpp               )
make_unit("unit.ieee" next.cpp                    )
make_unit("unit.ieee" prev.cpp                    )
#make_unit("unit.ieee" two_add.cpp                 )
#make_unit("unit.ieee" two_prod.cpp                )
make_unit("unit.ieee" ulpdist.cpp                 )
