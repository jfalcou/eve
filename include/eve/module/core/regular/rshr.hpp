//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/abs.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rshr
//!   @brief Computes the arithmetic right/left shift operation according to shift sign.
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
//!      template< eve::value T , integral_value N >
//!      T rshr(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  argument(@ref eve::value). to be shifted.
//!
//!     * `n`:    [shift](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!      The value of the arithmetic right/left shift operation according to shift
//!      sign is returned
//!
//!   @note
//!
//!     *  the call `rshr(x, n)` is equivalent to `if_else(n>0, shl(x, n), shr(x, n))`
//!        if `x`  is an  [simd value](@ref eve::simd_value).
//!
//!     *  The types must share the same cardinal or be scalar and if `N`
//!     *  is the size in bits  of the element type of `T`, all
//!     *  [elements](@ref glossary_elementwise) of n must belong to the
//!        interval: `]-N, N[` or the result is undefined.
//!
//!     * The call `rshr(x, n)` is equivalent to `x << n` if `x`  is
//!       an [simd value](@ref eve::simd_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/rshr.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::rshr[mask](x, ...)` provides a masked
//!     version of `rshr` which is
//!     equivalent to `if_else(mask, rshr(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/rshr.cpp}
//! @}
//================================================================================================

namespace tag
{
  struct rshr_;
}

namespace detail
{
  template<typename T, typename S>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::rshr_), T const&, [[maybe_unused]] S const& s)
  {
    EVE_ASSERT(assert_good_shift<T>(eve::abs(s)),
               "[eve::rshr] - Shifting by " << s << " is out of the range ]"
                                            << -int(sizeof(element_type_t<T>) * 8) << ", "
                                            << sizeof(element_type_t<T>) * 8 << "[.");
  }
}

EVE_MAKE_CALLABLE(rshr_, rshr);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/rshr.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rshr.hpp>
#endif
