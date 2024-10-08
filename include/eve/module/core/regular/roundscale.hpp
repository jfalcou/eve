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
  struct roundscale_t : strict_elementwise_callable<roundscale_t, Options, upward_option, downward_option,
                                                      to_nearest_option, toward_zero_option>
  {
    template<floating_value T0, integral_value T1>
    EVE_FORCEINLINE constexpr T0 operator()(T0 t0, T1 n) const noexcept
    {
      return this->behavior(as<T0>{}, eve::current_api, this->options(), t0, n);
    }

    template<floating_value T0, auto N>
    EVE_FORCEINLINE constexpr T0 operator()(T0 t0, index_t<N> n) const noexcept
    {
      return this->behavior(as<T0>{}, eve::current_api, this->options(), t0, n);
    }

    EVE_CALLABLE_OBJECT(roundscale_t, roundscale_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var roundscale
//!   @brief `strict_elementwise_callable` object computing the  scaled input rounding.
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
//!      constexpr auto roundscale(floating_value auto x, index_t<scale>)       noexcept; // 1
//!      constexpr auto roundscale(floating_value auto x, integral_value scale) noexcept; // 1
//!
//!      // Semantic option
//!      constexpr auto roundscale[downward](/*any of the above overloads*/)    noexcept; // 2
//!      constexpr auto roundscale[upward](/*any of the above overloads*/)      noexcept; // 2
//!      constexpr auto roundscale[to_nearest](/*any of the above overloads*/)  noexcept; // 2
//!      constexpr auto roundscale[toward_zero](/*any of the above overloads*/) noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`:      [floating value](@ref eve::floating_value).
//!      * `scale` : inttegal value or integral_constant of integral type.
//!
//!    **Return value**
//!
//!      1.  Returns the [elementwise](@ref glossary_elementwise) scaled input.
//!          The number of fraction bits retained is specified by scale. By default the internal
//!          rounding after scaling is done to nearest integer.
//!          The call `roundscale(x, scale)` is equivalent to  `ldexp(eve::nearest(ldexp(x,scale), -scale))`
//!      2. with `o` denoting one of these options the call is equivalent to ldexp(round[o](ldexp(x,scale), -scale))`
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/roundscale.cpp}
//================================================================================================
  inline constexpr auto roundscale = functor<roundscale_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/roundscale.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/roundscale.hpp>
#endif
