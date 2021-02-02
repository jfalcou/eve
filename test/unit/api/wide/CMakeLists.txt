##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## wide API tests
make_unit( "unit.api" std.cpp )

make_all_units(ROOT unit.api  NAME combine    ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME decrement  ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME increment  ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME load       ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME make       ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME slice      ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME splat      ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME storage    ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME store      ARCH simd TYPES ${all_types} )
make_all_units(ROOT unit.api  NAME swizzle    ARCH simd TYPES ${all_types} )
