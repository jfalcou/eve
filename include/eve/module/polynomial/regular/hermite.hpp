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
  struct hermite_t : elementwise_callable<hermite_t, Options, successor_option>
  {
    template<eve::floating_ordered_value ...Ts>
    constexpr EVE_FORCEINLINE
    eve::common_value_t<Ts ...> operator()(Ts...b) const noexcept
    {
      return EVE_DISPATCH_CALL(b...);
    }
    template<eve::integral_value T0, eve::floating_ordered_value ...Ts>
    constexpr EVE_FORCEINLINE
    as_wide_as_t<eve::common_value_t<Ts ...>, T0> operator()(T0 a, Ts...b) const noexcept
    {
      return EVE_DISPATCH_CALL(a, b...);
    }
    template<eve::integral_value T0, eve::integral_value T1, eve::floating_ordered_value ...Ts>
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
//!   @brief Computes the value of the 'physicists' Hermite polynomial of order `n` at `x`:
//!
//!   The physicists Hermite  polynomials are a sequence of orthogonal polynomials relative to
//!   \f$e^{-x^2}\f$ on the \f$[-\infty, +\infty]\f$ interval satisfying the following
//!   recurrence relation:
//!     * \f$ \mathbf{H}_0(x) = 1\f$.
//!     * \f$ \mathbf{H}_1(x) = 2x\f$.
//!     * \f$ \mathbf{H}_n(x) = 2x\mathbf{H}_{n-1}(x) -2(n-1)\mathbf{H}_{n-2}x\f$.
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
//!      eve::as_wide_as<T, N> hermite(N n, T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integral positive argument](@ref eve::integral_value).
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the 'physicists' hermite polynomial
//!   \f$ \displaystyle \mathbf{H}_n(x) = (-1)^n e^{x^2}\frac{d}{dx^n}e^{-x^2}\f$
//!   is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/polynomial/regular/hermite.cpp}
//!
//!   @groupheader{Semantic Modifiers}
//!
//!   * eve::successor
//!
//!     The expression `successor(hermite)(n, x, Hn, Hnm1)` implements the three terms recurrence
//!     relation for the physicists Hermite polynomials,
//!     \f$\displaystyle \mbox{H}_{n+1} = (2*x)\mbox{H}_{n}-2*n\mbox{H}_{n-1}\f$
//!
//!     This function can be used to create a sequence of values evaluated at the same `x`,
//!     and for rising `n`.
//!
//!     **Example**
//!
//!     @godbolt{doc/polynomial/successor/hermite.cpp}
//! @}
//================================================================================================
  inline constexpr auto hermite = functor<hermite_t>;
}

#include <eve/module/polynomial/regular/impl/hermite.hpp>
