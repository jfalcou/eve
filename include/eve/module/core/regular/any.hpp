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
//!   @var any
//!   @brief Computes a bool value which is true if and only if any elements of `x` is not zero.
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
//!      constexpr bool any(value auto x)                                              noexcept; // 1
//!      constexpr bool any(top_bits auto M t)                                         noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto any[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
//!      constexpr auto any[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
//!   }
//!   @endcode
//!    **Return value**
//!
//!      A bool value.
//!
//!   * 1. A bool value which is true if and only if any element of `x` is not zero.
//!     2. A masked version  which is true if and only if any retained elements of `x` are not zero.
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!    A bool value which is true if and only if any elements of `x` is not zero
//!    is returned.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/any.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(any_, any);
}

#include <eve/module/core/regular/impl/any.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/any.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/any.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/any.hpp>
#endif
