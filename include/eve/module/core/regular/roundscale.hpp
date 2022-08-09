//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/assert.hpp>
#include <eve/detail/overload.hpp>

#include <type_traits>

namespace eve
{
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
//!      template< eve::value T, int scale >
//!      T roundscale(T x, int scale) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`:      [floating value](@ref eve::floating_value).
//!      * `scale` : int or std::integral_constant of int type limited to the range [0, 15].
//!
//!    **Return value**
//!
//!       *  Returns the [elementwise](@ref glossary_elementwise) scaled input.
//!          The number of fraction bits retained is specified by scale. By default the internal
//!          rounding after scaling is done to nearest integer.
//!          `ldexp(round(ldexp(a0,scale),-scale))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/roundscale.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::roundscale[mask](x, scale)` provides a masked version of `eve::roundscale`
//!     which is equivalent to `if_else (mask, roundscale(x, scale), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/roundscale.cpp}
//!
//!    * eve::to_nearest, eve::toward_zero, eve::upward,  eve::downward
//!
//!      If d is one of these 4 decorators
//!      The call `d(roundscale)(x)`, call is equivalent to
//!      `eve::ldexp(d(eve::round)(eve::ldexp(a0,scale), -scale))`
//!
//!      @godbolt{doc/core/roundings/roundscale.cpp}
//! @}
//================================================================================================
namespace tag
{
  struct roundscale_;
}

namespace detail
{
  template<typename T>
  EVE_FORCEINLINE void
  check(EVE_MATCH_CALL(eve::tag::roundscale_), T const&, [[maybe_unused]] int s)
  {
    EVE_ASSERT(s >= 0 && s < 16, "[eve::roundscale] -  parameter s out of range [0, 15]: " << s);
  }
  template<int S, typename T>
  EVE_FORCEINLINE void
  check(EVE_MATCH_CALL(eve::tag::roundscale_), T const&, std::integral_constant<int, S> const&)
  {
    EVE_ASSERT(S >= 0 && S < 16,
               "[eve::roundscale] -  integral constant out of range [0, 15]: " << S);
  }
}

EVE_MAKE_CALLABLE(roundscale_, roundscale);
}

#include <eve/module/core/regular/impl/roundscale.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/roundscale.hpp>
#endif
