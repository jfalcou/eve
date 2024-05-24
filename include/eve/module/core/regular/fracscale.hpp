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
                                                      to_nearest_option, toward_zero_option, pedantic_option>
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
//!   @brief Computes the reduced part of the scaled input.
//!
//!   The call is equivalent to `a0-roundscale(a0,scale)`
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
//!      template< eve::floating_value T >
//!      T fracscale(T x, int scale) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`:      [real floating value](@ref eve::floating_value).
//!      * `scale` : int or std::integral_constant of int type limited to the range [0, 15].
//!
//!    **Return value**
//!
//!      Returns the [elementwise](@ref glossary_elementwise) reduced part of the scaled input.
//!      The number of fraction bits retained is specified by scale. By default the internal
//!      rounding after scaling is done to nearest integer.
//!      The call `fracscale(x, scale)` is equivalent to  `x-eve::ldexp(eve::nearest(eve::ldexp(x,scale), -scale))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/fracscale.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fracscale[mask](x, scale)` provides a masked version of `eve::fracscale`
//!     which is equivalent to `if_else (mask, eve::fracscale(x, scale), x)`.
//!
//!   * eve::to_nearest, eve::toward_zero, eve::upward,  eve::downward
//!
//!     If o is one of these 4 decorators
//!     The call `eve:fracscale[o](x, scale)` is equivalent to  `a0-d(eve::round[o](a0, scale)`
//!
//! @}
//================================================================================================
  inline constexpr auto fracscale = functor<fracscale_t>;
}

#include <eve/module/core/regular/impl/fracscale.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fracscale.hpp>
#endif
