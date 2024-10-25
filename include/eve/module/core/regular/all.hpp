//==================================================================================================
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
//================================================================================================
//! @addtogroup core_reduction
//! @{
//!   @var all
//!   @brief Computes a bool value which is true if and only if all elements of `x` are not zero.
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
//!      // Regular overloads
//!      constexpr auto all(logical_value auto x)                                      noexcept; // 1
//!      constexpr auto all(top_bits auto t)                                           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto all[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
//!      constexpr auto all[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::logical_value_value).
//!     * `t`: [top bits](@ref top_bits).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. A bool value which is true if and only if all elements of `x` are not zero.
//!      2. A masked version  which is true if and only if all retained elements of `x` are not zero.
//!
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/all.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(all_, all);
}

#include <eve/module/core/regular/impl/all.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/all.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/all.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/all.hpp>
#endif
