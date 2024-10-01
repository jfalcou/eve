//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>

namespace eve
{
  template<typename Options>
  struct firstbitset_t : elementwise_callable<firstbitset_t, Options>
  {
    template<integral_value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    {
      return EVE_DISPATCH_CALL_PT((as<T>{}), a);
    }

    EVE_CALLABLE_OBJECT(firstbitset_t, firstbitset_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var firstbitset
//!   @brief Computes [elementwise](@ref glossary_elementwise) the bit pattern
//!   in which the only bit set (if it exists) is the first bit set in the input.
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
//!      constexpr auto firstbitset(integral_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto firstbitset[conditional_expr auto c](integral_value auto x) noexcept; // 2
//!      constexpr auto firstbitset[logical_value auto m](integral_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [integral value](@ref integral_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. Computes [elementwise](@ref glossary_elementwise) the bit pattern in
//!         which the only bit set (if it exists) is
//!         the first bit set (beginning with the least significant bit) in the input.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/firstbitset.cpp}
//================================================================================================
  inline constexpr auto firstbitset = functor<firstbitset_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    firstbitset_(EVE_REQUIRES(cpu_), O const &, T a0) noexcept
    {
      return a0 & inc(~a0);
    }
  }
}
