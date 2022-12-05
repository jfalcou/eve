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
//!   @var laguerre
//!   @brief Computes the value of the Laguerre and associated
//!   Laguerre polynomials of order `n` at `x`:
//!
//!    * The Laguerre polynomial of order n is given by \f$\displaystyle \mbox{L}_{n}(x)
//!      = \frac{e^x}{n!}\frac{d^n}{dx^n}(x^ne^{-x})\f$.
//!    *  The associated laguerre polynomial is given by  \f$\displaystyle \mbox{L}_{n}^{m} =
//!      (-1)^m\frac{d^m}{dx^m}\mbox{L}_{n+m}(x)\f$.
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
//!     template< eve::integral_value N, eve::floating_ordered_value T >
//!      eve::as_wide_as<T, N> laguerre(N n, T x) noexcept;                               //1
//!
//!     template< eve::integral_value N, eve::integral_value M, eve::floating_ordered_value T >
//!      eve::as_wide_as<T, N> laguerre(N n, M m, T x) noexcept;                          //2
//!   }
//!   @endcode
//!
//!   1. Evaluate the laguerre polynomial of order n
//!   2. Evaluate the associated laguerre polynomial of orders n, m.
//!
//!   **Parameters**
//!
//!     * `n`, `m` :  [integral positive arguments](@ref eve::integral_value).
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!    **Return value**
//!
//!      The value of the polynomial at `x` is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/polynomial/regular/laguerre.cpp}
//!
//!   @groupheader{Semantic Modifiers}
//!
//!   * eve::successor
//!
//!     The expression `successor(laguerre)(n, x, ln, lnm1)` implements the three term
//!     recurrence relation for the Laguerre polynomials,
//!     \f$\displaystyle \mbox{L}_{n+1} =
//!     \left((2n+1-x)\mbox{L}_{n}-n\mbox{L}_{n-1}\right)/(n+1)\f$
//!
//!     The expression `successor(laguerre)(n, m, x, ln, lnmm1)` implements the three term
//!     recurrence relation for the associated Laguerre polynomials,
//!     \f$\displaystyle \mbox{L}_{n+1}^m =
//!     \left((m+2n+1-x)\mbox{L}_{n}^{m}-(m+n)\mbox{L}_{n-1}^{m}\right)/(n+1)\f$
//!
//!     These functions can be used to create a sequence of values evaluated at the same `x` (and
//!     `m`) and for rising `n`.
//!
//!     **Example**
//!
//!     @godbolt{doc/polynomial/successor/laguerre.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(laguerre_, laguerre);
}

#include <eve/module/polynomial/regular/impl/laguerre.hpp>
