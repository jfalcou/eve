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
//!   @var tchebeval
//!   @brief Evaluates a polynomial on the Tchebytchev polynomial basis.
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the polynomial,
//!   the Tchebeval scheme evaluates the polynom \f$\sum_0^{n-1} a_i T_{i}(x)\f$,
//!   where \f$T_{i}\f$ is the \f$i^{th}\f$ Tchebytchev polynomial of the first kind.
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
//!     template< eve::floating_real_value T, eve::floating_real_value Cs ...>
//!     T tchebeval(T x, Cs ... cs) noexcept;                                     // 1
//!
//!     template< eve::floating_real_value T, eve::range R>
//!     T tchebeval(T x, R r) noexcept;                                           // 2
//!
//!     template< eve::floating_real_value T, eve::floating_real_value U
//!             , eve::floating_real_value V, eve::range R>
//!     T tchebeval(T x, U a, V b,  R r) noexcept;                                // 3
//!   }
//!   @endcode
//!
//!   1. Evaluates the Tchebytchev polynomial using a variadic list of coefficients.
//!   2. Evaluates the Tchebytchev polynomial using a range of coefficients.
//!   3. Evaluates the Tchebytchev polynomial using a range of coefficients in interval `[a,b]`.
//!
//!   **Parameters**
//!
//!     * `x` : [real floating argument](@ref eve::floating_real_value).
//!
//!     * `a`, `b` : [real floating arguments](@ref eve::floating_real_value).
//!       If present,  they are the bounds of   the interval for which the Tchebytchev polynomial
//!       must be evaluated ( -1 and 1 by default). A change of variable
//!       \f$ x -> \frac{2x-a-b}{b-a}\f$ is internally performed.
//!
//!     * `cs`: [values ](@ref eve::value) expansion pack associated to the
//!        coefficients \f$(a_i)_{0\le i \lt n}\f$.
//!
//!     * `r` : [range](@ref eve::range) containing The polynomial coefficients.
//!
//!    **Return value**
//!
//!    the value of the polynom at  `x` is returned.
//!
//!    **Notes**
//!      If the coefficients are simd values of cardinal N, this means you simultaneously
//!      compute the values of N polynomials.
//!        *  If x is scalar, the polynomials are all computed at the same point
//!        *  If x is simd, the nth polynomial is computed on the nth value of x
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/polynomial/regular/tchebeval.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(tchebeval_, tchebeval);
}

#include <eve/module/polynomial/regular/impl/tchebeval.hpp>
