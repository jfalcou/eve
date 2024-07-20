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
//!   @var none
//!   @brief Computes a bool value which is true if and only if all elements of `x` are 0.
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
//!      constexpr auto none(logical_value auto x)                                      noexcept; // 1
//!      constexpr auto none(top_bits auto t)                                           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto none[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
//!      constexpr auto none[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref logical_value).
//!     * `t`: [top bits](@ref top_bits).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. A bool value which is true if and only if all elements of `x` are zero.
//!      2. A masked version  which is true if and only if all retained elements of `x` are zero.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/none.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(none_, none);
}

#include <eve/module/core/regular/impl/none.hpp>
