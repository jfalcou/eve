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
//! These functions provide scalar and SIMD version of basic bitwise functions.
//!
//! To keep the results homogeneous and coherent between SIMD and scalar mode, the types usable
//! in those functions are generally required to satisfy `eve::bit_compatible_values`
//!
//! **Convenience header:** @code{.cpp} #include <eve/function/bit.hpp> @endcode
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
