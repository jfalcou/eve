##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

add_custom_target(unit.bessel.exe         )
add_dependencies(unit.exe unit.bessel.exe )

make_unit("unit.bessel"  airy.cpp           )
make_unit("unit.bessel"  airy_ai.cpp        )
make_unit("unit.bessel"  airy_bi.cpp        )
make_unit("unit.bessel"  cyl_bessel_i0.cpp  )
make_unit("unit.bessel"  cyl_bessel_i1.cpp  )
make_unit("unit.bessel"  cyl_bessel_in.cpp  )
make_unit("unit.bessel"  cyl_bessel_j0.cpp  )
make_unit("unit.bessel"  cyl_bessel_j1.cpp  )
make_unit("unit.bessel"  cyl_bessel_jn.cpp  )
make_unit("unit.bessel"  cyl_bessel_k0.cpp  )
make_unit("unit.bessel"  cyl_bessel_k1.cpp  )
make_unit("unit.bessel"  cyl_bessel_kn.cpp  )
make_unit("unit.bessel"  cyl_bessel_y0.cpp  )
make_unit("unit.bessel"  cyl_bessel_y1.cpp  )
make_unit("unit.bessel"  cyl_bessel_yn.cpp  )

make_unit("unit.bessel"  sph_bessel_j0.cpp  )
make_unit("unit.bessel"  sph_bessel_j1.cpp  )
make_unit("unit.bessel"  sph_bessel_jn.cpp  )
#make_unit("unit.bessel"  sph_bessel_y0.cpp  )
#make_unit("unit.bessel"  sph_bessel_y1.cpp  )
#make_unit("unit.bessel"  sph_bessel_yn.cpp  )
