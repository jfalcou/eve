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
      return EVE_DISPATCH_CALL(t0, n);
    }

    template<floating_value T0, auto N>
    EVE_FORCEINLINE constexpr T0 operator()(T0 t0, index_t<N> const & n) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, n);
    }

    EVE_CALLABLE_OBJECT(roundscale_t, roundscale_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var roundscale
//!   @brief Computes the  scaled input rounding.
//!
//!   **Defined in Header**
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
//!      template< eve::value T, auto scale >
//!      T roundscale(T x,  index_t<scale> ) noexcept;
//!  
//!      template< eve::value T>
//!      T roundscale(T x, int scale) noexcept;
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
//!       *  Returns the [elementwise](@ref glossary_elementwise) scaled input.
//!          The number of fraction bits retained is specified by scale. By default the internal
//!          rounding after scaling is done to nearest integer.
//!          The call `roundscale(x, scale)` is equivalent to  `eve::ldexp(eve::nearest(eve::ldexp(x,scale), -scale))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/roundscale.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::roundscale[mask](x, scale)` provides a masked version of `eve::roundscale`
//!     which is equivalent to `if_else (mask, roundscale(x, scale), x)`.
//!
//!    * eve::to_nearest, eve::toward_zero, eve::upward,  eve::downward
//!
//!      If o is one of these 4 decorators
//!      The call `roundscale[o](x)` is equivalent to
//!      `eve::ldexp(eve::round[o](eve::ldexp(x,scale), -scale))`
//!
//! @}
//================================================================================================
  inline constexpr auto roundscale = functor<roundscale_t>;
}

#include <eve/module/core/regular/impl/roundscale.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/roundscale.hpp>
#endif
