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
#include <eve/module/core/regular/countr_zero.hpp>
#include <bit>

namespace eve
{
  template<typename Options>
  struct countr_one_t : elementwise_callable<countr_one_t, Options>
  {
    template<eve::unsigned_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(countr_one_t, countr_one_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var countr_one
//!   @brief `elementwise_callable` object computing the number of consecutive bits set in a value starting from right.
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
//!      constexpr auto countr_one(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto countr_one[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto countr_one[logical_value auto m](value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!       1.The value of the number of consecutive 1 ("one") bits in the value of `x`, starting
//!         from the least significant bit ("right"), with same type as `x`, is returned.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/countr_one)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/countr_one.cpp}
//! @}
//================================================================================================
  inline constexpr auto countr_one = functor<countr_one_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T countr_one_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      if constexpr( scalar_value<T> )
        return T(std::countr_one(v));
      else
        return countr_zero(~v);
    }
  }
}
