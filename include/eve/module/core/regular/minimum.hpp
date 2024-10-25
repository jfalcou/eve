/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//DOC TODO
//================================================================================================
//! @addtogroup core_reduction
//! @{
//!   @var minimum
//!   @brief Computes the minimal value in a simd vector
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
//!      constexpr auto minimum(value auto x)                          noexcept; // 1;
//!
//!      // Lanes masking
//!      constexpr auto minimum[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto minimum[logical_value auto m](value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameter**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The minimal value of all lanes.
//!     2. The  minimal value of the retained lanes
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/minimum.cpp}
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(minimum_, minimum);
}

#include <eve/module/core/regular/impl/minimum.hpp>

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/minimum.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/minimum.hpp>
#endif
