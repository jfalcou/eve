//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var reverse_horner
//!   @brief implement the horner scheme to evaluate polynomials with coefficients
//!  in incresing power order
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by increasing
//!   power order,  the Reverse_Horner scheme evaluates the polynom \f$p\f$ at \f$x\f$ by :
//!   \f$\displaystyle p(x) = (((a_{n-1}x+a_{n-2})x+ ... )x + a_0)\f$
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
//!     template< eve::floating_real_value T, eve::floating_real_value C ...>
//!     T reverse_horner(T x, C ... coefs) noexcept;                                   //1
//!
//!     template< eve::floating_real_value T, eve::Range R>
//!     T reverse_horner(T x, R r) noexcept;                                           //2
//!
//!   }
//!   @endcode
//!
//!   1) polynom is evaluated at x the other inputs are the polynomial coeficients.
//!   2) polynom is evaluated at x the other input is a range containing the coefficients
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!     * `...coefs` :  [real floating arguments](@ref eve::floating_real_value).
//!        The coefficients by increasing power order
//!
//!     * `r` :  [range](@ref eve::range) containing The coefficients by increasing power order.
//!
//!    **Return value**
//!
//!    the value of the polynom at `x` is returned.
//!
//!    **Notes**
//!      If the coefficients are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/polynomial/regular/reverse_horner.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::pedantic, eve::numeric
//!
//!       If d denotes one of these modifiers, the expression `d(eve::reverse_horner)(...)`
//!       computes the result using `d(eve::fma)` instead of `eve::fma` in internal computations.
//!
//!       This is intended to insure more accurate computations where needed. This has no cost if
//!       the system has hard wired fma but is very expansive if it is not the case.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(reverse_horner_, reverse_horner);
}

#include <eve/module/polynomial/regular/impl/reverse_horner.hpp>
