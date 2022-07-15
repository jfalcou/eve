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
  //!   @var newton
  //!   @brief implement the Newton scheme to evaluate polynomials.
  //!
  //!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial by decreasing
  //!   power order,  and \f$(c_i)_{0\le i\le n-2}\f$ the nodes, the Newton scheme evaluates
  //!   the polynom \f$p\f$ at \f$x\f$ by :
  //!   \f$ \displaystyle p(x) = (((a_0(x-c_0)+a_1)(x-c_1)+ ... )(x-c_{n-2}) + a_{n-1})\f$
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
  //!      template< eve::floating_real_value T, eve::Range C, eve::Range N>
  //!     T newton(T x, C c, N n) noexcept;                                           //2
  //!
  //!   }
  //!   @endcode
  //!
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real_value).
  //!
  //!
  //!     * `r` :  [range](@ref eve::range) containing The coefficients by decreasing power order.
  //!
  //!     * `n` :  [range](@ref eve::range) containing The nodes by decreasing power order.
  //!
  //!    **Return value**
  //!
  //!    the value of the polynom at  `x` is returned.
  //!
  //!    **Notes**
  //!      If the coefficients or nodes are simd values of cardinal N, this means you simultaneously
  //!      compute the values of N polynomials.
  //!        *  If x is scalar, the polynomials are all computed at the same point
  //!        *  If x is simd, the nth polynomial is computed on the nth value of x
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/polynomial/regular/newton.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!  * eve::pedantic, eve::numeric
  //!
  //!       If d denotes one of these modifiers, the expression `d(eve::newton)(...)`
  //!       computes the result using `d(eve::fma)` instead of `eve::fma` in
  //!       internal computation`.
  //!
  //!       This is intended to insure more accurate computations where needed. This has no cost if
  //!       the system has hard wired fma but is very expansive if it is not the case.
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(newton_, newton);
}

#include <eve/module/polynomial/regular/impl/newton.hpp>
