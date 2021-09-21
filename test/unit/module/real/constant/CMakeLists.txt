##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.real.constant.exe       )

##==================================================================================================
## new style tests
##==================================================================================================
make_unit("unit.real.constant"  basic.cpp                  )
make_unit("unit.real.constant"  ieee754.cpp                )
make_unit("unit.real.constant"  limit.cpp                  )
make_unit("unit.real.constant"  math.cpp                   )

##==================================================================================================
## Other Constant tests old style
make_unit( "unit.real.constant" constant.cpp     )
