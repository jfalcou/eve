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
//! @defgroup trigonometric Trigonometric
//!
//! These functions provide scalar and SIMD version of trigonometric functions.
//!
//! Moreover all trigonometric direct functions (except sinc and sinpic)  provide 4 decorators flavours :
//!
//!   The possible decorators are:
//!
//!    * quarter_circle: the fastest but gives the correct result in \f$[-\pi/4, +\pi/4]\f$ only and Nan outside.
//!    * half_circle: gives the correct result for \f$[-\pi/2, +\pi/2]\f$ only and Nan outside.
//!    * full_circle: gives the correct result for \f$[-\pi, +\pi]\f$ only and Nan outside.
//!    * medium:  gives the correct result for \f$|x| < 536870912.0f\f$ (float) or  \f$ |x| < 2.0e14 \f$ (double)
//!    * big: gives the correct result in the whole range.
//!
//!      Without any decorator the call tests the input value to choose among the decorated ones the best fit.
//!      Of course, with SIMD parameter the fit is the interval containing all the vector elements.
//!
//!      The rationale to provide these flavours is that the more costly part of the computation of a
//!      trigonometric function from the radian angle
//!      is the reduction of the argument modulo  \f$\pi/4\f$ that, to be correct in the full range must use
//!      a few hundreds of  \f$\pi\f$ decimals:
//!
//!    - if \f$x \in [-\pi/4, +\pi/4]\f$ there is no reduction to perform.
//!    - if \f$x \in [-\pi, +\pi]\f$ the work is not a lot heavier.
//!    - if \f$x\f$ in  the medium range a simplified scheme can be used.
//!    - for the whole range a quite heavy algorithm is to be used.
//!
//! **Convenience header:** @code{.cpp} #include <eve/function/trigonometric.hpp> @endcode
//!
//!@}
//================================================================================================

#include <eve/function/cos.hpp>
#include <eve/function/cosd.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/cot.hpp>
#include <eve/function/cotd.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/function/csc.hpp>
#include <eve/function/cscd.hpp>
#include <eve/function/cscpi.hpp>
#include <eve/function/sec.hpp>
#include <eve/function/secd.hpp>
#include <eve/function/secpi.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/sinc.hpp>
#include <eve/function/sind.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/function/sinpic.hpp>
#include <eve/function/tan.hpp>
#include <eve/function/tand.hpp>
#include <eve/function/tanpi.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/function/radinpi.hpp>
