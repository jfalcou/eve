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
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_shr
//!   @brief Computes a logical right shift.
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
//!      T bit_shr(T x, N n) noexcept;
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
//!    The value of the logical right shift
//!    is returned.
//!
//!   @note
//!     * The call `bit_shr(x, n)` is equivalent to `x >> n` if `x`  is
//!       an [simd value](@ref eve::simd_value).
//!
//!     * The types must share the same cardinal or be scalar and if \f$N\f$
//!       is the size in bits  of the element type of `T`,
//!       all elements of n must belong to the
//!       interval: \f$[0, N[\f$ or the result is undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_shr.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_shr[mask](x, ...)` provides a masked
//!     version of `bit_shr` which is
//!     equivalent to `if_else(mask, bit_shr(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_shr.cpp}
//! @}
//================================================================================================
namespace tag
{
  struct bit_shr_;
}

namespace detail
{
  template<typename T, typename S>
  EVE_FORCEINLINE void
  check(EVE_MATCH_CALL(eve::tag::bit_shr_), T const&,
        [[maybe_unused]] S const& s)
  {
    EVE_ASSERT(assert_good_shift<T>(s),
               "[eve::bit_shr] Shifting by " << s << " is out of the range [0, "
                                             << sizeof(element_type_t<T>) * 8 << "[.");
  }

  template<conditional_expr C, typename T, typename S>
  EVE_FORCEINLINE void
  check(EVE_MATCH_CALL(eve::tag::bit_shr_), C const& , T const&,
        [[maybe_unused]] S const& s)
  {
    EVE_ASSERT(assert_good_shift<T>(s),
               "[eve::bit_shr] Shifting by " << s << " is out of the range [0, "
                                             << sizeof(element_type_t<T>) * 8 << "[.");
  }
}

EVE_MAKE_CALLABLE(bit_shr_, bit_shr);
}

#include <eve/module/core/regular/impl/bit_shr.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_shr.hpp>
#endif
