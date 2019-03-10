##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2018 Joel FALCOU
##  Copyright 2019 Jean-Thierry Lapreste
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================

##==================================================================================================
## documentation tests
add_unit_test( "doc.function.arithmetic" abs.cpp )
add_unit_test( "doc.function.arithmetic" bitwise_shl.cpp )
add_unit_test( "doc.function.arithmetic" is_denormal.cpp )
add_unit_test( "doc.function.arithmetic" shl.cpp )
add_unit_test( "doc.function.arithmetic" shr.cpp )
add_unit_test( "doc.function.bitwise" bitwise_and.cpp )
add_unit_test( "doc.function.bitwise" bitwise_andnot.cpp )
add_unit_test( "doc.function.bitwise" bitwise_cast.cpp )
add_unit_test( "doc.function.bitwise" bitwise_mask.cpp )
add_unit_test( "doc.function.bitwise" bitwise_not.cpp )
add_unit_test( "doc.function.bitwise" bitwise_notand.cpp )
add_unit_test( "doc.function.bitwise" bitwise_notor.cpp )
add_unit_test( "doc.function.bitwise" bitwise_or.cpp )
add_unit_test( "doc.function.bitwise" bitwise_ornot.cpp )
add_unit_test( "doc.function.bitwise" bitwise_select.cpp )
add_unit_test( "doc.function.bitwise" bitwise_shl.cpp )
add_unit_test( "doc.function.bitwise" bitwise_shr.cpp )
add_unit_test( "doc.function.bitwise" bitwise_xor.cpp )
add_unit_test( "doc.function.logical" logical_and.cpp )
add_unit_test( "doc.function.logical" logical_andnot.cpp )
add_unit_test( "doc.function.logical" logical_not.cpp )
add_unit_test( "doc.function.logical" logical_notand.cpp )
add_unit_test( "doc.function.logical" logical_notor.cpp )
add_unit_test( "doc.function.logical" logical_or.cpp )
add_unit_test( "doc.function.logical" logical_ornot.cpp )
add_unit_test( "doc.function.logical" logical_xor.cpp )
add_unit_test( "doc.function.operators" add.cpp )
add_unit_test( "doc.function.operators" sub.cpp )
add_unit_test( "doc.function.predicate" is_equal.cpp )
add_unit_test( "doc.function.predicate" is_equal_with_equal_nans.cpp )
add_unit_test( "doc.function.predicate" is_finite.cpp )
add_unit_test( "doc.function.predicate" is_inf.cpp )
add_unit_test( "doc.function.predicate" is_nan.cpp )
add_unit_test( "doc.function.predicate" is_not_equal_with_equal_nans.cpp )
add_unit_test( "doc.function.predicate" is_not_finite.cpp )
add_unit_test( "doc.function.predicate" is_not_inf.cpp )
add_unit_test( "doc.function.predicate" is_not_nan.cpp )
add_unit_test( "doc.function.predicate" is_unordered.cpp )
