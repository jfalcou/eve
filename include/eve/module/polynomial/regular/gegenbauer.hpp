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
  struct gegenbauer_t : strict_elementwise_callable<gegenbauer_t, Options>
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

    EVE_CALLABLE_OBJECT(gegenbauer_t, gegenbauer_);
  };

//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var gegenbauer
//!   @brief  `strict_elementwise_callable` object computing the value of a  gegenbauer
//!           polynomial \f$ \mathbf{C}_n^\lambda(x)\f$.
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
//!     constexpr auto gegenbauer(integral_value auto n, floating_value auto lambda,
//!                               floating_value auto x)                                                    noexcept; //1
//!
//!      // Lanes masking
//!      constexpr auto gegenbauer[conditional_expr auto c](integral_value auto n, floating_value auto lambda,
//!                                                         floating_value auto x)                          noexcept; // 2
//!      constexpr auto gegenbauer[logical_value auto m](integral_value auto n, floating_value auto lambda,
//!                                                      floating_value auto x)                             noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: [integral argument](@ref eve::integral_value).
//!     * `lambda`: [real floating argument](@ref eve::floating_value). Must be greater than \f$-\frac12\f$.
//!     * `x`: [real floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of \f$ \mathbf{C}_n^\lambda(x)\f$ is returned.
//!
//!        The Gegenbauer polynomials are a sequence of orthogonal polynomials relative to
//!        \f$(1-x^2)^{\lambda-1/2}\f$ on the \f$[-1, +1]\f$ interval satisfying the following
//!        recurrence relation:
//!          * \f$ \mathbf{C}_0^\lambda(x) = 1\f$.
//!          * \f$ \mathbf{C}_1^\lambda(x) = 2\lambda x\f$.
//!          * \f$ \mathbf{C}_n^\lambda(x) = \left[(2x+\lambda-1)\mathbf{C}_{n-1}^\lambda(x) -
//!            (n+2\lambda-2)\mathbf{C}_{n-2}^\lambda(x)\right]/n\f$.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Abel_polynomials)
//!   *  [Wolfram MathWorld](https://en.wikipedia.org/wiki/Gegenbauer_polynomials)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/polynomial/regular/gegenbauer.cpp}
//! @}
//================================================================================================
  inline constexpr auto gegenbauer = functor<gegenbauer_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/polynomial/regular/impl/gegenbauer.hpp>
