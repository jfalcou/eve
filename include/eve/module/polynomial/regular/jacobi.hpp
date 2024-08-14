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
  struct jacobi_t : strict_elementwise_callable<jacobi_t, Options>
  {
    template<eve::floating_value ...Ts>
    requires (same_lanes_or_scalar<Ts...>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<Ts ...> operator()(Ts...b) const noexcept
    {
      return EVE_DISPATCH_CALL(b...);
    }
    template<eve::integral_value T0, eve::floating_value ...Ts>
    requires (same_lanes_or_scalar<T0, Ts...>)
    constexpr EVE_FORCEINLINE
    as_wide_as_t<eve::common_value_t<Ts ...>, T0> operator()(T0 a, Ts...b) const noexcept
    {
      return EVE_DISPATCH_CALL(a, b...);
    }
    EVE_CALLABLE_OBJECT(jacobi_t, jacobi_);
  };

//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var jacobi
//!   @brief `strict_elementwise_callable` object computing the value of the Jacobi polynomials \f$P^{\alpha, \beta}_n(x)\f$.
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
//!     // Regular overload
//!     constexpr auto jacobi(integral_value auto n, floating_value auto x,
//!                               floating_value auto alpha, floating_value auto beta)                         noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto jacobi[conditional_expr auto c](integral_value auto n, floating_value auto x,
//!                                                      floating_value auto alpha,  floating_value auto beta) noexcept; // 2
//!      constexpr auto jacobi[logical_value auto m](integral_value auto n, floating_value auto x,
//!                                                   floating_value auto alpha,  floating_value auto beta)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integral positive argument](@ref eve::integral_value).
//!     * `x` :  [real floating argument](@ref eve::floating_value).
//!     * `alpha`, `beta`: [floating arguments](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!     The Jacobi  polynomials are a sequence of orthogonal polynomials relative
//!     to \f$(1-x)^{\alpha}(1+x)^{\beta}\f$, for \f$\alpha \f$ and \f$\beta \f$ greater than -1,
//!     on the \f$[-1, +1]\f$ interval.
//!
//!     They can be defined via a Rodrigues formula:
//!      \f$\displaystyle P^{\alpha, \beta}_n(x) = \frac{(-1)^n}{2^n n!}(1-x)^{-\alpha}
//!     (1+x)^{-\beta} \frac{d}{dx^n}\left\{ (1-x)^{\alpha}(1+x)^{\beta}(1-x^2)^n \right\}\f$.
//!
//!    1. The value of the polynomial \f$P^{\alpha, \beta}_n(x)\f$ is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Classical Orthogonal Polynomials](https://dlmf.nist.gov/18.3)
//!   *  [Wikipedia:Jacobi
   _polynomial](https://en.wikipedia.org/wiki/Jacobi_polynomials)
//!   *  [Wolfram MathWorld:Jacobi Polynomial](https://mathworld.wolfram.com/JacobiPolynomial.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/polynomial/regular/jacobi.cpp}
//================================================================================================
  inline constexpr auto jacobi = functor<jacobi_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/polynomial/regular/impl/jacobi.hpp>
