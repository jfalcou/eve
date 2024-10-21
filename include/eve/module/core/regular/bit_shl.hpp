//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/shl.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_bitops
  //! @{
  //!   @var bit_shl
  //!   @brief `strict_elementwise_callable` object computing a logical left shift.
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
  //!      constexpr auto bit_shl(integral_value auto, x integral_value auto n)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto bit_shl[conditional_expr auto c](integral_value auto x, integral_value auto n) noexcept; // 2
  //!      constexpr auto bit_shl[logical_value auto m](integral_value auto x, integral_value auto n)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: argument(@ref eve::integral_value). to be shifted.
  //!     * `n`: [shift](@ref eve::integral_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!    **Return value**
  //!       1. The value of the logical left shift is returned.
  //!       2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!   @note
  //!     * The call `bit_shl(x, n)` is equivalent to `x << n` if `x`  is
  //!       an [simd value](@ref eve::simd_value).
  //!
  //!     * The types must share the same cardinal or be scalar and if \f$N\f$
  //!       is the size in bits  of the element type of `x`, all elements of n must belong to the
  //!       interval \f$[0, N[\f$ or the result is undefined.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/bit_shl.cpp}
  //================================================================================================
  inline constexpr auto bit_shl = functor<shl_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}
