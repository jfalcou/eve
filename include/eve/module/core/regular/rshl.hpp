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
//!   @var rshl
//!   @brief Computes the arithmetic left/right shift operation according to shift sign.
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
//!      T rshl(T x, N n) noexcept;
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
//!      The value of the arithmetic left/right shift operation according to shift
//!      sign is returned
//!
//!   @note
//!     *  the call `rshl(x, n)` is equivalent to `if_else(n>0, shl(x, n), shr(x, n))`
//!        if `x`  is an  [simd value](@ref eve::simd_value).
//!
//!     *  The types must share the same cardinal or be scalar and if `N`
//!     *  is the size in bits  of the element type of `T`, all
//!     *  [elements](@ref glossary_elementwise) of n must belong to the
//!        interval: `]-N, N[` or the result is undefined.
//!
//!     * The call `rshl(x, n)` is equivalent to `x << n` if `x`  is
//!       an [simd value](@ref eve::simd_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/rshl.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::rshl[mask](x, ...)` provides a masked
//!     version of `rshl` which is
//!     equivalent to `if_else(mask, rshl(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/rshl.cpp}
//! @}
//================================================================================================

namespace tag
{
  struct rshl_;
}

namespace detail
{
  template<typename T, typename S>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::rshl_), T const&, [[maybe_unused]] S const& s)
  {
    EVE_ASSERT(assert_good_shift<T>(eve::abs(s)),
               "[eve::rshl] - Shifting by " << s << " is out of the range ]"
                                            << -int(sizeof(element_type_t<T>) * 8) << ", "
                                            << sizeof(element_type_t<T>) * 8 << "[.");
  }
}

EVE_MAKE_CALLABLE(rshl_, rshl);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/rshl.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rshl.hpp>
#endif
