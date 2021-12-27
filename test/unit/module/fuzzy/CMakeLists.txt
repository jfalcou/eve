##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.fuzzy.exe                    )


##==================================================================================================
## new style tests
##==================================================================================================
make_unit("unit.fuzzy" ceil.cpp                     )
make_unit("unit.fuzzy" floor.cpp                    )
make_unit("unit.fuzzy" is_equal.cpp                 )
make_unit("unit.fuzzy" is_greater_equal.cpp         )
make_unit("unit.fuzzy" is_greater.cpp               )
make_unit("unit.fuzzy" is_less_equal.cpp            )
make_unit("unit.fuzzy" is_less.cpp                  )
make_unit("unit.fuzzy" is_not_equal.cpp             )
make_unit("unit.fuzzy" is_not_greater_equal.cpp     )
make_unit("unit.fuzzy" is_not_greater.cpp           )
make_unit("unit.fuzzy" is_not_less_equal.cpp        )
make_unit("unit.fuzzy" is_not_less.cpp              )
make_unit("unit.fuzzy" trunc.cpp                    )
