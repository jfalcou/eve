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
make_unit("random.core" average.cpp             )
