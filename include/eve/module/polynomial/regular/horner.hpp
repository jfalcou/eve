//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var horner
//!   @brief Implement the horner scheme to evaluate polynomials/
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
//!   power order,  the Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
//!   \f$\displaystyle p(x) = (((a_0x+a_1)x+ ... )x + a_{n-1})\f$
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/polynomial.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template< eve::floating_ordered_value T, eve::floating_ordered_value C ...>
//!     T horner(T x, C ... coefs) noexcept;                                   //1
//!
//!     template< eve::floating_ordered_value T, eve::Range R>
//!     T horner(T x, R r) noexcept;                                           //2
//!
//!   }
//!   @endcode
//!
//!   1. Polynom is evaluated at x the other inputs are the polynomial coefficients.
//!   2. Polynom is evaluated at x the other input is a range containing the coefficients
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!     * `coefs...` :  [real floating arguments](@ref eve::floating_ordered_value).
//!        The coefficients by decreasing power order
//!
//!     * `r` : Range containing The coefficients by decreasing power order.
//!
//!   **Return value**
//!
//!   The value of the polynom at  `x` is returned.
//!
//!    **Notes**
//!
//!      If the coefficients are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/polynomial/regular/horner.cpp}
//!
//!   @groupheader{Semantic Modifiers}
//!
//!   * eve::pedantic, eve::numeric
//!
//!       If d denotes one of these modifiers, the expression `d(eve::horner)(...)`
//!       computes the result using `d(eve::fma)` instead of `eve::fma` in internal computations.
//!
//!       This is intended to insure more accurate computations where needed. This has no cost if
//!       the system has hard wired fma but is very expansive if it is not the case.
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(horner_, horner);
}

#include <eve/module/polynomial/regular/impl/horner.hpp>
