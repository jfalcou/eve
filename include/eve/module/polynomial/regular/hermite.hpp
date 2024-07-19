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
  struct hermite_t : strict_elementwise_callable<hermite_t, Options, successor_option>
  {
    template<eve::floating_ordered_value ...Ts>
    requires (same_lanes_or_scalar<Ts...>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<Ts ...> operator()(Ts...b) const noexcept
    {
      return EVE_DISPATCH_CALL(b...);
    }
    template<eve::integral_value T0, eve::floating_ordered_value ...Ts>
    requires (same_lanes_or_scalar<T0, Ts...>)
    constexpr EVE_FORCEINLINE
    as_wide_as_t<eve::common_value_t<Ts ...>, T0> operator()(T0 a, Ts...b) const noexcept
    {
      return EVE_DISPATCH_CALL(a, b...);
    }
    template<eve::integral_value T0, eve::integral_value T1, eve::floating_ordered_value ...Ts>
    requires (same_lanes_or_scalar<T0, T1, Ts...>)
    constexpr EVE_FORCEINLINE
    as_wide_as_t<eve::common_value_t<Ts ...>, eve::common_value_t<T0, T1>> operator()(T0 a, T1 b, Ts...c) const noexcept
    {
      return EVE_DISPATCH_CALL(a, b, c...);
    }

    EVE_CALLABLE_OBJECT(hermite_t, hermite_);
  };

//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var hermite
//!   @brief  `strict_elementwise_callable` object computing the value of the 'physicists' Hermite polynomial of order `n` at `x`:
//!
//!   The physicists Hermite polynomials are a sequence of orthogonal polynomials relative to
//!   \f$e^{-x^2}\f$ on the \f$[-\infty, +\infty]\f$ interval satisfying the following
//!   recurrence relation:
//!     * \f$ \mathbf{H}_0(x) = 1\f$.
//!     * \f$ \mathbf{H}_1(x) = 2x\f$.
//!     * \f$ \mathbf{H}_n(x) = 2x\mathbf{H}_{n-1}(x) -2(n-1)\mathbf{H}_{n-2}x\f$.
//!
//!   @groupheader{Callable Signatures}
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
//!      constexpr auto hermite(integral_value auto n, floating_value auto x)                          noexcept; //1
//!
//!      // Lanes masking
//!      constexpr auto hermite[conditional_expr auto c](integral_value auto n, floating_value auto x) noexcept; // 2
//!      constexpr auto hermite[logical_value auto m](integral_value auto n, floating_value auto x)    noexcept; // 2
//!
//!      // Semantic option
//!      constexpr auto hermite(integral_value auto n, floating_value auto x,
//!                            floating_value auto hn, floating_value auto hnm1)                      noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: [integral positive argument](@ref eve::integral_value).
//!     * `x`: [real floating argument](@ref eve::floating_ordered_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the 'physicists' hermite polynomial
//!        \f$ \displaystyle \mathbf{H}_n(x) = (-1)^n e^{x^2}\frac{d}{dx^n}e^{-x^2}\f$
//!        is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. implements the three terms recurrence
//!        relation for the physicists Hermite polynomials,
//!        \f$\displaystyle \mbox{H}_{n+1} = (2*x)\mbox{H}_{n}-2*n\mbox{H}_{n-1}\f$.
//!        This call can be used to create a sequence of values evaluated at the same `x`,
//!        and for rising `n`.
//!
//!  @groupheader{External references}
//!   *  [DLMF](https://dlmf.nist.gov/18.3)
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/special_functions/hermite)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/HermitePolynomial.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/polynomial/regular/hermite.cpp}
//! @}
//================================================================================================
  inline constexpr auto hermite = functor<hermite_t>;
}

#include <eve/module/polynomial/regular/impl/hermite.hpp>
