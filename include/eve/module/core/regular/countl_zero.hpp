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
  struct countl_zero_t : elementwise_callable<countl_zero_t, Options>
  {
    template<eve::unsigned_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(countl_zero_t, countl_zero_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var countl_zero
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
//!      constexpr auto countl_zero(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking 
//!      constexpr auto countl_zero[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto countl_zero[logical_value auto m](value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!       1. The value of the number of consecutive 0 ("zero") bits in the value of `x`, starting
//!        from the most significant bit ("left"), with same type as `x` is returned.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/countl_zero)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/countl_zero.cpp}
//! @}
//================================================================================================
  inline constexpr auto countl_zero = functor<countl_zero_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T countl_zero_(EVE_REQUIRES(cpu_), O const&, T const& x) noexcept
    {
      if constexpr( scalar_value<T> )
        return T(std::countl_zero(x));
      else
        return map(countl_zero, x);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/countl_zero.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/countl_zero.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/countl_zero.hpp>
#endif
