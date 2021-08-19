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
//! @defgroup ieee754 Ieee754
//!
//! These functions provide scalar and SIMD version of functions related to the representation of
//! floating point values.
//!
//! **Convenience header:** @code{.cpp} #include <eve/function/ieee_754.hpp> @endcode
//!
//!@}
//================================================================================================

#include <eve/function/bitofsign.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/mantissa.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/function/next.hpp>
#include <eve/function/nextafter.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/two_add.hpp>
#include <eve/function/two_prod.hpp>
#include <eve/function/two_split.hpp>
#include <eve/function/ulpdist.hpp>
