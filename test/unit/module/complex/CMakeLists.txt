##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(unit.complex.exe          )
add_dependencies(unit.exe unit.complex.exe  )

make_unit("unit.complex"  abs.cpp           )
make_unit("unit.complex"  constructor.cpp   )
make_unit("unit.complex"  i.cpp             )
make_unit("unit.complex"  imag.cpp          )
make_unit("unit.complex"  if_else.cpp       )
make_unit("unit.complex"  is_finite.cpp     )
make_unit("unit.complex"  is_imag.cpp       )
make_unit("unit.complex"  is_infinite.cpp   )
make_unit("unit.complex"  is_nan.cpp        )
make_unit("unit.complex"  is_not_finite.cpp )
make_unit("unit.complex"  is_real.cpp       )
make_unit("unit.complex"  operators.cpp     )
make_unit("unit.complex"  proj.cpp          )
make_unit("unit.complex"  real.cpp          )
## make_unit("unit.complex"  sqr.cpp           )
make_unit("unit.complex"  acos.cpp          )
make_unit("unit.complex"  acosh.cpp         )
make_unit("unit.complex"  asin.cpp          )
make_unit("unit.complex"  asinh.cpp         )
make_unit("unit.complex"  atan.cpp          )
make_unit("unit.complex"  atanh.cpp          )
make_unit("unit.complex"  cos.cpp           )
make_unit("unit.complex"  cosh.cpp          )