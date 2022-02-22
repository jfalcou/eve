##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
add_custom_target(random.core.exe           )
add_dependencies(random.exe random.core.exe )

##==================================================================================================
## tests
##==================================================================================================
make_unit("random.core" abs.cpp                 )
make_unit("random.core" arg.cpp                 )
make_unit("random.core" average.cpp             )
make_unit("random.core" bit_ceil.cpp            )
make_unit("random.core" bit_floor.cpp           )
make_unit("random.core" bit_mask.cpp            )
make_unit("random.core" bit_not.cpp             )
make_unit("random.core" bit_width.cpp           )
make_unit("random.core" bitofsign.cpp           )
make_unit("random.core" ceil.cpp                )
##make_unit("random.core" conj.cpp                ) ->math
make_unit("random.core" dec.cpp                 )
make_unit("random.core" exponent.cpp            )
make_unit("random.core" firstbitset.cpp         )
make_unit("random.core" firstbitunset.cpp       )
make_unit("random.core" floor.cpp               )
make_unit("random.core" frac.cpp                )
##make_unit("random.core" frexp.cpp               )
##make_unit("random.core" ifrexp.cpp              )
make_unit("random.core" inc.cpp                 )
make_unit("random.core" is_denormal.cpp         )
make_unit("random.core" is_eqz.cpp              )
make_unit("random.core" is_gez.cpp              )
make_unit("random.core" is_gtz.cpp              )
make_unit("random.core" is_lez.cpp              )
make_unit("random.core" is_ltz.cpp              )
make_unit("random.core" is_nez.cpp              )
make_unit("random.core" mantissa.cpp            )
make_unit("random.core" trunc.cpp               )
