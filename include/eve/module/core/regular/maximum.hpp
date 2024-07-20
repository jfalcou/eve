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
//!   @var maximum
//!   @brief Computes the maximal value in a simd vector
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
//!      constexpr auto maximum(value auto x)                          noexcept; // 1;
//!
//!      // Lanes masking
//!      constexpr auto maximum[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto maximum[logical_value auto m](value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameter**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The  maximal value of all lanes.
//!     2. The maximal value of the retained lanes.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/maximum.cpp}
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(maximum_, maximum);
}

#include <eve/module/core/regular/impl/maximum.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/maximum.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/maximum.hpp>
#endif
