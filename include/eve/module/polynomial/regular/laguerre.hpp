//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct laguerre_t : strict_elementwise_callable<laguerre_t, Options, associated_option>
  {
    template<eve::integral_value N, eve::floating_value T>
    constexpr EVE_FORCEINLINE eve::as_wide_as_t<T, N> operator()(N n, T t) const
    {
      return EVE_DISPATCH_CALL(n,t);
    }

    template<eve::integral_value N, eve::integral_value M, eve::floating_value T>
    constexpr EVE_FORCEINLINE eve::as_wide_as_t<T, common_value_t<M,N>> operator()(N n, M m, T t) const
    {
      return EVE_DISPATCH_CALL(n, m, t);
    }

    EVE_CALLABLE_OBJECT(laguerre_t, laguerre_);
  };

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
//!     template< eve::integral_value N, eve::floating_value T >
//!     constexpr eve::as_wide_as_t<T, N> laguerre(N n, T x) noexcept;                                              // 1
//!
//!     template< eve::integral_value N, eve::integral_value M, eve::floating_value T >
//!     constexpr eve::eve::as_wide_as_t<T, eve::common_type_t<M,N>> laguerre[associated](N n, M m, T x) noexcept;  // 2
//!   }
//!   @endcode
//!
//!   1. Evaluate the laguerre polynomial of order n
//!   2. Evaluate the associated laguerre polynomial of orders n, m.
//!
//!   **Parameters**
//!
//!     * `n`, m` :  [integral positive arguments](@ref eve::integral_value).
//!     * `x` :  [real floating argument](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!    The value of the polynomial at `x` is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/polynomial/regular/laguerre.cpp}
//!
//!   @groupheader{Semantic Modifier}
//!
//!   * eve::successor
//!
//!     The expression `laguerre[successor](n, x, ln, lnm1)` implements the three term
//!     recurrence relation for the Laguerre polynomials,
//!     \f$\displaystyle \mbox{L}_{n+1} =
//!     \left((2n+1-x)\mbox{L}_{n}-n\mbox{L}_{n-1}\right)/(n+1)\f$
//!
//!     The expression `laguerre[associated][successor](n, m, x, ln, lnmm1)` implements the three term
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
 inline constexpr auto laguerre = functor<laguerre_t>;
}

#include <eve/module/polynomial/regular/impl/laguerre.hpp>
