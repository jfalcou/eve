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
  struct tchebytchev_t : strict_elementwise_callable< tchebytchev_t, Options
                                                    , successor_option, kind_1_option, kind_2_option
                                                    >
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

    EVE_CALLABLE_OBJECT(tchebytchev_t, tchebytchev_);
  };

//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var tchebytchev
//!   @brief Computes the value of the Tchebytchev polynomial of order `n` at `x`:
//!
//!    * The Tchebytchev polynomial of order n is given by \f$ \displaystyle \mbox{T}_{n}(x)
//!      = \cos(n\arccos(x))\f$ on \f$[-1, +1]\f$
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
//!     constexpr auto tchebytchev(integral_value auto n, floating_value auto x)                           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto tchebytchev[conditional_expr auto c](integral_value auto n, floating_value auto x) noexcept; // 2
//!      constexpr auto tchebytchev[logical_value auto m](integral_value auto n, floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto tchebytchev[kind_1](integral_value auto n, floating_value auto x)                  noexcept; // 1
//!      constexpr auto tchebytchev[kind_2](integral_value auto n, floating_value auto x)                  noexcept; // 3
//!      constexpr auto tchebytchev[successor](floating_value auto x, integral_value auto tn,
//!                                                                   integral_value auto tnm1)            noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integral positive arguments](@ref eve::integral_value).
//!     * `x` :  [real floating argument](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!      1.The value of the polynomial at `x` is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. evaluates the nth polynomial of tchebytchev of second kind
//!         \f$ \displaystyle U_n(x) =  \frac{\sin(n\arccos x)}{\sin(\arccos x)}\f$.
//!         on \f$[-1, +1]\f$.
//!      4. computes the value of \f$T_{n+1}(x)\f$ knowing the values tn = \f$T_n(x)\f$ and
//!         tnm1 = \f$T_{n-1}(x)\f$,
//!         This call can be used to create a sequence of values evaluated at the same `x`
//!         and for rising `n`.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia]( https://en.wikipedia.org/wiki/Chebyshev_polynomials)
//!   *  [Wolfram MathWorld first kind](https://mathworld.wolfram.com/ChebyshevPolynomialoftheFirstKind.html)
//!   *  [Wolfram MathWorld second kind](https://mathworld.wolfram.com/ChebyshevPolynomialoftheSecondKind.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/polynomial/regular/tchebytchev.cpp}
//!   @godbolt{doc/polynomial/successor/tchebytchev.cpp}
//! @}
//================================================================================================
  inline constexpr auto tchebytchev = functor<tchebytchev_t>;
}

#include <eve/module/polynomial/regular/impl/tchebytchev.hpp>
