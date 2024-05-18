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
//!     constexpr eve::as_wide_as<T, N> tchebytchev(N n, T x) noexcept;
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
  inline constexpr auto tchebytchev = functor<tchebytchev_t>;
}

#include <eve/module/polynomial/regular/impl/tchebytchev.hpp>
