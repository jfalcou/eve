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
  struct fracscale_t : strict_elementwise_callable<fracscale_t, Options, upward_option, downward_option,
                                                      to_nearest_option, toward_zero_option>
  {
    template<floating_value T0, integral_value T1>
    EVE_FORCEINLINE constexpr T0 operator()(T0 t0, T1 n) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, n);
    }

    template<floating_value T0, auto N>
    EVE_FORCEINLINE constexpr T0 operator()(T0 t0, index_t<N> const & n) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, n);
    }

    EVE_CALLABLE_OBJECT(fracscale_t, fracscale_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fracscale
//!   @brief `strict_elementwise_callable` object computing the reduced part of the scaled input.
//!
//!   The call is equivalent to `a0-roundscale(a0,scale)`
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto fracscale(floating_value auto x, index_t<scale>)       noexcept; // 1
//!      constexpr auto fracscale(floating_value auto x, integral_value scale) noexcept; // 1
//!
//!      // Semantic option
//!      constexpr auto fracscale[downward](/*any of the above overloads*/)    noexcept; // 2
//!      constexpr auto fracscale[upward](/*any of the above overloads*/)      noexcept; // 2
//!      constexpr auto fracscale[to_nearest](/*any of the above overloads*/)  noexcept; // 2
//!      constexpr auto fracscale[toward_zero](/*any of the above overloads*/) noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`:      [real floating value](@ref eve::floating_value).
//!      * `scale` : int or std::integral_constant of int type limited to the range [0, 15].
//!
//!   **Return value**
//!
//!      1. Returns the [elementwise](@ref glossary_elementwise) reduced part of the scaled input.
//!         The number of fraction bits retained is specified by scale. By default the internal
//!         rounding after scaling is done to nearest integer.
//!         The call `fracscale(x, scale)` is equivalent to  `x-eve::ldexp(eve::nearest(eve::ldexp(x,scale), -scale))`
//!      2. with `o` denoting one of these options the call is equivalent to `x-eve::roundscale[o](x, scale)`
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/fracscale.cpp}
//! @}
//================================================================================================
  inline constexpr auto fracscale = functor<fracscale_t>;
}

#include <eve/module/core/regular/impl/fracscale.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fracscale.hpp>
#endif
