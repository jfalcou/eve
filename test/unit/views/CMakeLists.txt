##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Project Contributors
##  SPDX-License-Identifier: BSL-1.0
##==================================================================================================

##==================================================================================================
## Setup aggregation of tests
##==================================================================================================
add_custom_target(unit.views.exe       )

##==================================================================================================
## VIEWS tests

make_unit("unit.views" backward.cpp)
make_unit("unit.views" backward_eve_iterator.cpp)
make_unit("unit.views" convert_zip.cpp)
make_unit("unit.views" convert.cpp)
make_unit("unit.views" converting_eve_iterator.cpp)
make_unit("unit.views" iota.cpp)
make_unit("unit.views" preprocess_zip_range.cpp)
make_unit("unit.views" map.cpp)
make_unit("unit.views" map_eve_iterator.cpp)
make_unit("unit.views" reverse.cpp)
make_unit("unit.views" reverse_eve_iterator.cpp)
make_unit("unit.views" zip_iterator.cpp)
make_unit("unit.views" zip.cpp)
