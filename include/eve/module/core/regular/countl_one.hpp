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
#include <eve/module/core/regular/countl_zero.hpp>
#include <bit>

namespace eve
{
  template<typename Options>
  struct countl_one_t : elementwise_callable<countl_one_t, Options>
  {
    template<unsigned_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((T), v);
    }

    EVE_CALLABLE_OBJECT(countl_one_t, countl_one_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var countl_one
//!   @brief elementwise_callable` object computing the number of consecutive bits unset in a value starting from left
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
//!      constexpr auto countl_one(unsigned_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto countl_one[conditional_expr auto c](unsigned_value auto x) noexcept; // 2
//!      constexpr auto countl_one[logical_value auto m](unsigned_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve:unsigned_:value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!       1. The value of the number of consecutive 1 ("one") bits in the value of `x`, starting
//!        from the most significant bit ("left"), with same type as `x` is returned.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/countl_one)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/countl_one.cpp}
//================================================================================================
  inline constexpr auto countl_one = functor<countl_one_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T countl_one_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      if constexpr( scalar_value<T> )
        return T(std::countl_one(v));
      else
        return countl_zero(~v);
    }
  }
}
