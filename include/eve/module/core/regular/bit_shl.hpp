//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/shl.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_bitops
  //! @{
  //!   @var bit_shl
  //!   @brief Computes a logical left shift.
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
  //!      T bit_shl(T x, N n) noexcept;
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
  //!    The value of the logical left shift
  //!    is returned.
  //!
  //!   **Notes**
  //!
  //!     * The call `bit_shl(x, n)` is equivalent to `x << n` if `x`  is
  //!       an [simd value](@ref eve::simd_value).
  //!
  //!     * The types must share the same cardinal or be scalar and if \f$N\f$
  //!       is the size in bits  of the element type of `T`,
  //!       all elements of n must belong to the
  //!       interval: \f$[0, N[\f$ or the result is undefined.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/bit_shl.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::bit_shl[mask](x, ...)` provides a masked
  //!     version of `bit_shl` which is
  //!     equivalent to `if_else(mask, bit_shl(x, ...), x)`
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/bit_shl.cpp}
  //! @}
  //================================================================================================
  EVE_ALIAS_CALLABLE(shl_, bit_shl);
}
