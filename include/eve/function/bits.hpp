//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

//================================================================================================
//! @addtogroup functions
//! @{
//! @defgroup bits Bits
//!
//! @brief Scalar and SIMD version of basic bitwise functions.
//!
//! These functions provide scalar and SIMD version of bit operations. These operations are extended
//! to work on any [value](@ref eve::value) types by considering the bitwise operation to apply
//! on the value bit patterns while retaining its original types, thus following the @ref glossary_bitwise
//! semantic.
//!
//! If a bitwise operation implies a negation -- as in `bit_andnot`-- the position of the
//! negation in the function's name matches the position of the negated parameter. For example,
//! `bit_andnot(x,y)` is semantically equivalent to `bit_and(x,bit_not(y))` but may be optimized.
//!
//! **Convenience header:** @code{.cpp} #include <eve/function/bits.hpp> @endcode
//!
//!@}
//================================================================================================
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_ceil.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/firstbitset.hpp>
#include <eve/function/firstbitunset.hpp>
#include <eve/function/bit_floor.hpp>
#include <eve/function/is_pow2.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/function/bit_notand.hpp>
#include <eve/function/bit_notor.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_ornot.hpp>
#include <eve/function/bit_select.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/bit_shl.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/countl_one.hpp>
#include <eve/function/countr_one.hpp>
#include <eve/function/countl_zero.hpp>
#include <eve/function/countr_zero.hpp>
#include <eve/function/next.hpp>
#include <eve/function/nextafter.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/popcount.hpp>
#include <eve/function/bit_width.hpp>
