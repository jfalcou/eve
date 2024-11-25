//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/bit_notand.hpp>

namespace eve
{
  template<typename Options>
  struct firstbitunset_t : elementwise_callable<firstbitunset_t, Options>
  {
    template<integral_value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), a);
    }

    EVE_CALLABLE_OBJECT(firstbitunset_t, firstbitunset_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var firstbitunset
//!   @brief Computes [elementwise](@ref glossary_elementwise) the bit pattern
//!   in which the only bit set (if it exists) is the first bit unset in the input.
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
//!      constexpr auto firstbitunset(integral_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto firstbitunset[conditional_expr auto c](integral_value auto x) noexcept; // 2
//!      constexpr auto firstbitunset[logical_value auto m](integral_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [integral value](@ref eve::integral_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. Computes [elementwise](@ref glossary_elementwise) the bit pattern in
//!         which the only bit set (if it exists) is the first bit unset (beginning with the least
//!         significant bit) in the input.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/firstbitunset.cpp}
//================================================================================================
  inline constexpr auto firstbitunset = functor<firstbitunset_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    firstbitunset_(EVE_REQUIRES(cpu_), O const &, T a0) noexcept
    {
     if constexpr( scalar_value<T> )
        return ~a0 & inc(a0);
      else
        return bit_notand(a0, inc(a0));
    }
  }
}
