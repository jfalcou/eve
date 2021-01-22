##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018-2021 Joel FALCOU
##  Copyright 2018-2021 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

build_test( "arch"  main.cpp
                    is_supported.cpp
                    current_api.cpp
                    expected_cardinal.cpp
          )
