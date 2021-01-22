##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018-2021 Joel FALCOU
##  Copyright 2018-2021 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

build_test( "meta"  main.cpp
                    as_floating_point.cpp
                    as_integer.cpp
                    as_wide.cpp
                    sign_of.cpp
                    rebindable.cpp
                    decorator.cpp
                    value.cpp
                    native_simd_for_abi.cpp
                    cardinal.cpp
                    has_abi.cpp
                    element_type.cpp
          )
