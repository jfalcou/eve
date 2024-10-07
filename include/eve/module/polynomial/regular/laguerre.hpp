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
    template<integral_value N, floating_value T>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, N> operator()(N n, T t) const
      requires (same_lanes_or_scalar<N, T>)
    {
      return EVE_DISPATCH_CALL_PT((as_wide_as_t<T, N>), n, t);
    }

    template<integral_value N, integral_value M, floating_value T>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, common_value_t<M, N>> operator()(N n, M m, T t) const
      requires (same_lanes_or_scalar<N, M, T>)
    {
      return EVE_DISPATCH_CALL_PT((as_wide_as_t<T, common_value_t<M, N>>), n, m, t);
    }

    EVE_CALLABLE_OBJECT(laguerre_t, laguerre_);
  };

  //================================================================================================
  //! @addtogroup polynomial
  //! @{
  //!   @var laguerre
  //!   @brief `strict_elementwise_callable` object computing the value of the Laguerre and associated
  //!   Laguerre polynomials of order `n` at `x`:
  //!
  //!    * The Laguerre polynomial of order n is given by \f$\displaystyle \mbox{L}_{n}(x)
  //!      = \frac{e^x}{n!}\frac{d^n}{dx^n}(x^ne^{-x})\f$.
  //!    *  The associated laguerre polynomial is given by  \f$\displaystyle \mbox{L}_{n}^{m} =
  //!      (-1)^m\frac{d^m}{dx^m}\mbox{L}_{n+m}(x)\f$.
  //!
  //!   @groupheader{Header file}
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
  //!      // Regular overload
  //!      constexpr auto laguerre(integral_value auto n, floating_value auto x)                 noexcept; //1
  //!
  //!      // Semantic options
  //!      constexpr auto laguerre[associated](integral_value auto n, integral_value auto m,
  //!                                          floating_value auto x)                            noexcept; // 2
  //!      constexpr auto laguerre[successor](integral_value auto n,
  //!                                          floating_value auto x,
  //!                                          integral_value auto ln, integral_value auto lnm1) noexcept; // 3
  //!      constexpr auto laguerre[successor](integral_value auto n, integral_value auto l,
  //!                                          floating_value auto x,
  //!                                          integral_value auto ln, integral_value auto lnm1) noexcept; // 3
  //!      constexpr auto laguerre[associated][successor](integral_value auto n,
  //!                                          integral_value auto m, floating_value auto x)     noexcept; // 4
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`, `m`, `l`, `ln`, `lnm1` : [integral positive arguments](@ref integral_value).
  //!     * `x` : [floating argument](@ref floating_value).
  //!
  //!   **Return value**
  //!
  //!      1. The value of the Laguerre polynomial of order `n` at `x` is returned.
  //!      2. The value of the associated Laguerre polynomial of orders `n`, `m` at `x` is returned.
  //!      constexpr auto legendre(integral_value auto n, floating_value auto x)             noexcept; //1
  //!      3. implements the three term  recurrence relation for the Laguerre polynomials,
  //!        \f$\displaystyle \mbox{L}_{n+1} = \left((2n+1-x)\mbox{L}_{n}-n\mbox{L}_{n-1}\right)/(n+1)\f$
  //!      4. implements the three term  recurrence relation for the associated Laguerre polynomials,
  //!        \f$\displaystyle \mbox{L}_{n+1}^m = \left((m+2n+1-x)\mbox{L}_{n}^{m}-(m+n)\mbox{L}_{n-1}^{m}\right)/(n+1)\f$
  //!
  //!  @groupheader{External references}
  //!   *  [DLMF: Classical Orthogonal Polynomials](https://dlmf.nist.gov/18.3)
  //!   *  [C++ standard reference: laguerre](https://en.cppreference.com/w/cpp/numeric/special_functions/laguerre)
  //!   *  [Wolfram MathWorld: Laguerre Polynomial](https://mathworld.wolfram.com/LaguerrePolynomial.html)
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/polynomial/regular/laguerre.cpp}
  //================================================================================================
  inline constexpr auto laguerre = functor<laguerre_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/polynomial/regular/impl/laguerre.hpp>
