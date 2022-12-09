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
//!   @var tchebytchev
//!   @brief Computes the value of the Tchebytchev polynomial of order `n` at `x`:
//!
//!    * The Tchebytchev polynomial of order n is given by \f$ \displaystyle \mbox{T}_{n}(x)
//!      = \cos(n\arccos(x))\f$ on \f$[-1, +1]\f$
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
//!      eve::as_wide_as<T, N> tchebytchev(N n, T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integral positive arguments](@ref eve::integral_value).
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!    **Return value**
//!
//!    The value of the polynomial at `x` is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/polynomial/regular/tchebytchev.cpp}
//!
//!   @groupheader{Semantic Modifiers}
//!
//!   * eve::kind_1, eve::kind_2
//!
//!     The expression `kind_1(tchebytchev)(n,x)` is identical to `tchebytchev(n,x)`.
//!     The expression `kind_2(tchebytchev)(n,x)` evaluates the nth polynomial of tchebytchev of
//!     second kind \f$ \displaystyle U_n(x) =  \frac{\sin(n\arccos x)}{\sin(\arccos x)}\f$ at `x`
//!     on \f$[-1, +1]\f$.
//!
//!     **Example**
//!
//!     @godbolt{doc/polynomial/kind/tchebytchev.cpp}
//!
//!   * eve::successor
//!
//!     The expression `successor(tchebytchev)( x, tn, tnm1)` computes the value of
//!     \f$T_{n+1}(x)\f$ knowing the values tn = \f$T_n(x)\f$ and   tnm1 = \f$T_{n-1}(x)\f$,
//!
//!     This function can be used to create a sequence of values evaluated at the same `x`
//!     and for rising `n`.
//!
//!     **Example**
//!
//!     @godbolt{doc/polynomial/successor/tchebytchev.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(tchebytchev_, tchebytchev);
}

#include <eve/module/polynomial/regular/impl/tchebytchev.hpp>
