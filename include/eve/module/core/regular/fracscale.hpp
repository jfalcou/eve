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
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/ldexp.hpp>
#include <eve/module/core/regular/nearest.hpp>

namespace eve
{
  template<typename Options>
  struct fracscale_t : strict_elementwise_callable<fracscale_t, Options,  downward_option, upward_option,
                                to_nearest_option, toward_zero_option>
  {
    template<eve::floating_value T, integral_scalar_value S>
    EVE_FORCEINLINE constexpr T
    operator()(T t, S s) const noexcept
    {
      EVE_ASSERT(s >= 0 && s < 16, "[eve::fracscale] -  parameter s out of range [0, 15]: " << s);
      return EVE_DISPATCH_CALL(t, s);
    }

    template<eve::floating_value T, auto S>
    EVE_FORCEINLINE constexpr T
    operator()(T t, std::integral_constant<int, S> const & s) const noexcept
    {
      EVE_ASSERT(S >= 0 && S < 16, "[eve::fracscale] -  integral constant out of range [0, 15]: " << S);
      return EVE_DISPATCH_CALL(t, s);
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
//!      template< eve::floating_value T, int scale >
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
//!     If d is one of these 4 decorators
//!     The call `d(eve:fracscale)(x, scale)`, call is equivalent to  `a0-d(eve::roundscale)(a0, scale)`
//!
//! @}
//================================================================================================
  inline constexpr auto fracscale = functor<fracscale_t>;

  namespace detail
  {
    template<typename T, typename S, callable_options O>
    EVE_FORCEINLINE constexpr T
    fracscale_(EVE_REQUIRES(cpu_), O const &, T const &a0, S scale) noexcept
    {
      return if_else(is_infinite(a0), zero, a0 - ldexp(nearest(ldexp(a0, scale)), -scale));
    }

    template<typename T, auto S, callable_options O>
    EVE_FORCEINLINE constexpr T
    fracscale_(EVE_REQUIRES(cpu_), O const &, T const &a0, std::integral_constant<int, S> scale) noexcept
    {
      return if_else(is_infinite(a0), zero, a0 - ldexp(nearest(ldexp(a0, S)), -S));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fracscale.hpp>
#endif
