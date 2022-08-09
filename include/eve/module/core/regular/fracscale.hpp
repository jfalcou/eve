//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
//!   @var fracscale
//!   @brief Computes the reduced part of the scaled input.
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
//!      T fracscale(T x, int scale) noexcept;
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
//!       *  Returns the [elementwise](@ref glossary_elementwise) reduced part of the scaled input.
//!          The number of fraction bits retained is specified by scale. By default the internal
//!          rounding after scaling is done to nearest integer.
//!          The call is equivalent to `a0-roundscale(a0,scale)`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/fracscale.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fracscale[mask](x, scale)` provides a masked version of `eve::fracscale`
//!     which is equivalent to `if_else (mask, eve::fracscale(x, scale), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/fracscale.cpp}
//!
//!   * eve::to_nearest, eve::toward_zero, eve::upward,  eve::downward
//!
//!     If d is one of these 4 decorators
//!     The call `d(eve:fracscale)(x, scale)`, call is equivalent to  `a0-d(eve::roundscale)(a0, scale)`
//!
//!      @godbolt{doc/core/roundings/fracscale.cpp}
//! @}
//================================================================================================
namespace tag
{
  struct fracscale_;
}

namespace detail
{
  template<typename T>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::fracscale_), T const&, [[maybe_unused]] int s)
  {
    EVE_ASSERT(s >= 0 && s < 16, "[eve::fracscale] -  parameter s out of range [0, 15]: " << s);
  }
  template<int S, typename T>
  EVE_FORCEINLINE void
  check(EVE_MATCH_CALL(eve::tag::fracscale_), T const&, std::integral_constant<int, S> const&)
  {
    EVE_ASSERT(S >= 0 && S < 16,
               "[eve::fracscale] -  integral constant out of range [0, 15]: " << S);
  }
}

EVE_MAKE_CALLABLE(fracscale_, fracscale);
}

#include <eve/module/core/regular/impl/fracscale.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fracscale.hpp>
#endif
