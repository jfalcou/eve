//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct countr_zero_t : elementwise_callable<countr_zero_t, Options>
  {
    template<eve::unsigned_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(countr_zero_t, countr_zero_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var countr_zero
//!   @brief `elementwise_callable` object computing the number of consecutive bits unset in a value starting from right.
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
//!      constexpr auto countr_zero(unsigned_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto countr_zero[conditional_expr auto c](unsigned_value auto x) noexcept; // 2
//!      constexpr auto countr_zero[logical_value auto m](unsigned_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      The value of the number of consecutive 0 ("zero") bits in the value of `x`, starting
//!      from the least significant bit ("right"), with same type as `x`, is returned.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/countr_zero)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/countr_zero.cpp}
//================================================================================================
  inline constexpr auto countr_zero = functor<countr_zero_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/countr_zero.hpp>

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/countr_zero.hpp>
#endif
