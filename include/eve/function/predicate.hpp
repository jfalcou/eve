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
//! @defgroup predicates Predicates
//!
//! These functions provide scalar and SIMD version of predicate functions.
//!
//! Take take that these function objects in **SIMD** mode do not return a boolean but a logical
//! **SIMD** value,
//!
//! **Convenience header:** @code{.cpp} #include <eve/function/predicate.hpp> @endcode
//!
//!@}
//================================================================================================

#include <eve/function/is_denormal.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_imag.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_normal.hpp>
#include <eve/function/is_not_denormal.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_flint.hpp>
#include <eve/function/is_not_imag.hpp>
#include <eve/function/is_not_infinite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/is_not_real.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/is_ordered.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_real.hpp>
#include <eve/function/is_unordered.hpp>
