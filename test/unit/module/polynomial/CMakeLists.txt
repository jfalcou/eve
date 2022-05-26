##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(unit.polynomial.exe                )
add_dependencies(unit.exe unit.polynomial.exe        )


make_unit("unit.polynomial"  tchebytchev.cpp         )
make_unit("unit.polynomial"  tchebeval.cpp           )
make_unit("unit.polynomial"  gegenbauer.cpp          )
make_unit("unit.polynomial"  hermite.cpp             )
make_unit("unit.polynomial"  horner.cpp              )
make_unit("unit.polynomial"  laguerre.cpp            )
make_unit("unit.polynomial"  legendre.cpp            )
make_unit("unit.polynomial"  newton.cpp              )
make_unit("unit.polynomial"  reverse_horner.cpp      )
make_unit("unit.polynomial"  polynom_constructor.cpp )
make_unit("unit.polynomial"  polynom_young.cpp       )
make_unit("unit.polynomial"  polynom_concat.cpp      )
make_unit("unit.polynomial"  polynom_degree.cpp      )
make_unit("unit.polynomial"  polynom_mul.cpp         )
make_unit("unit.polynomial"  polynom_add.cpp         )
make_unit("unit.polynomial"  polynom_sub.cpp         )
make_unit("unit.polynomial"  polynom_remquo.cpp      )
make_unit("unit.polynomial"  polynom_div.cpp         )
make_unit("unit.polynomial"  polynom_valuation.cpp   )
make_unit("unit.polynomial"  polynom_evaluation.cpp  )
make_unit("unit.polynomial"  polynom_derivatives.cpp )
make_unit("unit.polynomial"  polynom_primitives.cpp  )
make_unit("unit.polynomial"  polynom_operators.cpp   )
make_unit("unit.polynomial"  sparse_polynom_add.cpp         )
make_unit("unit.polynomial"  sparse_polynom_constructor.cpp )
make_unit("unit.polynomial"  sparse_polynom_degree.cpp      )
make_unit("unit.polynomial"  sparse_polynom_evaluation.cpp  )
make_unit("unit.polynomial"  sparse_polynom_operators.cpp   )
make_unit("unit.polynomial"  sparse_polynom_valuation.cpp   )
