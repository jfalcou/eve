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
//!   @var count_true
//!   @brief Computes the number of non 0 elements
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
//!      constexpr auto count_true(logical_value auto x)                                      noexcept; // 1
//!      constexpr auto count_true(top_bits auto t)                                           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto count_true[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
//!      constexpr auto count_true[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
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
//!      1. The value in the element type of `x`  of the number of non 0 elements.
//!      2. A masked version  which return the number of true retained elements.
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of the number of non 0 elements
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/count_true.cpp}
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::$name$[mask](x, ...)` provides a masked
//!     version of `count_true which count the non masked non zero element
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(count_true_, count_true);
}

#include <eve/module/core/regular/impl/count_true.hpp>

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/count_true.hpp>
#endif
