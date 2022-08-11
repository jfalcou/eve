//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup functions
//! @{
//! @defgroup math  Mathematical functions
//! @brief Current Mathematical functions
//!
//! This module provides implementation for
//! scalar and SIMD versions of mathematical functions, mainly libc++ ones.
//!
//! **Required header:** @code{.cpp} #include <eve/module/math.hpp> @endcode
//!
//! @}
//==================================================================================================

//==================================================================================================
//! @addtogroup math
//! @{
//!
//! @defgroup math_constants  Constants
//! @ingroup math
//! These functions allows access to salar and SIMD values of some mathematical constants.
//! In particular,  all libc++ constants are here, sometimes with a different name.
//!
//! All floating mathematical constants supports a regular call and two decorated calls:
//!
//!  * the regular call provides the floating point representation that is nearest to the
//!    mathematical value,
//!  * eve::upward provides the least representable value that is greater than
//!    the mathematical value,
//!  * eve::downward provides the greatesst representable value that is lrss than the
//!    mathematical value,
//!
//!  About constants names:
//!
//!    * When a name contains an _ it means that preceeding the underscore is a
//!     'function or multiplication  that must be applied to the following parts:
//!
//!        * log_2 stands for \f$\log(2)\f$ the natural logarithm of 2
//!        * log2_e stands for \f$\log2(e)\f$  the  logarithm in base 2 of the euler constant,
//!        * inv_pi is the inverse of \f$\pi\f$.
//!        * four_pio_3 stands for \f$4\pi/3\f$ (the `o` meanings over).
//!
//! @defgroup math_trig  Trigonometric
//! @ingroup math
//! These functions allows performing trigonometric computations
//!
//! All trigonometric functions exists in three flavors for parameters being radian,
//!   degrees or \f$\pi\f$ multiples.
//!
//!   * for example eve::cos,  eve::cosd,  eve::cospi.
//!
//! Moreover each function can be decorated with eve::quarter_circle,  eve:half_circle,
//! eve::full_circle, eve::medium,  eve::big.
//!
//!   * eve::quarter_circle provides accurates result for the corresonding
//!     radian angle in\f$]-\pi/4,\pi/4[\f$,  Nan outside
//!   * eve::half_circle provides accurates result for the corresonding
//!     radian angle in\f$]-\pi/2,\pi/2[\f$,  Nan outside
//!   * eve::full_circle provides accurates result for the corresonding
//!     radian angle in\f$]-\pi,\pi[\f$,  Nan outside
//!   * eve::medium provides accurates result for the corresonding
//!     radian angle in a reasonnable interval,  with degrading accuracy outside
//!   * eve::big provides accurates result in the full range
//!   * regular call (not decorated) choose the best call.
//!
//! see [trigonometry rationale](@ref trigo_rationale) for more details
//!
//! @defgroup math_invtrig  Inverse trigonometric
//! @ingroup math
//! These functions allows performing trigonometric computations
//!
//! @defgroup math_hyper  Hyperbolic
//! @ingroup math
//! These functions allows performing Hyperbolic computations
//!
//! @defgroup math_invhyper  Inverse hyperbolic
//! @ingroup math
//! These functions allows performing Inverse hyperbolic computations
//!
//! @defgroup math_log  Logarithm
//! @ingroup math
//! These functions allows performing logarithms computations
//!
//! @defgroup math_exp  Exponential
//! @ingroup math
//! These functions allows performing exponentials computations
//!
//! @}
//==================================================================================================

#include <eve/module/math/constant/math.hpp>
#include <eve/module/math/decorator/math.hpp>
#include <eve/module/math/regular/math.hpp>
#include <eve/module/math/pedantic/math.hpp>
