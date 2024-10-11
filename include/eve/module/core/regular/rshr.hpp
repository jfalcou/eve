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

namespace eve
{
  template<typename Options>
  struct rshr_t : strict_elementwise_callable<rshr_t, Options>
  {
    template<integral_value T, integral_value N>
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N> operator()(T t0, N s) const noexcept
      requires(eve::same_lanes_or_scalar<T, N>)
    {                 
      return EVE_DISPATCH_CALL(t0, s);
    }

    template<integral_value T, std::ptrdiff_t S>
    EVE_FORCEINLINE constexpr T operator()(T t0, index_t<S> s) const noexcept
    {
      constexpr std::ptrdiff_t l = sizeof(element_type_t<T>) * 8;
      static_assert((S < l) && (S > -l), "[eve::rshr] Shift value is out of range.");

      return EVE_DISPATCH_CALL(t0, s);
    }

    EVE_CALLABLE_OBJECT(rshr_t, rshr_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rshr
//!   @brief Computes the arithmetic right/left shift operation according to shift sign.
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
//!      constexpr auto rshr(integral_value auto x, integral_value auto n)                          noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto rshr[conditional_expr auto c](integral_value auto x, integral_value auto n) noexcept; // 3
//!      constexpr auto rshr[logical_value auto m](integral_value auto x, integral_value auto n)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value) to be shifted.
//!     * `n`: [shift](@ref eve::integral_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!       1. The value of the arithmetic right/left shift operation according to shift
//!          sign is returned. This equivalent to `if_else(n>0, shl(x, n), shr(x, -n))`.
//!          If `N` is the size in bits  of the element type of `T`, all
//!          [elements](@ref glossary_elementwise) of n must belong to the
//!          interval: `]-N, N[` or the result is undefined.
//!      2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/rshr.cpp}
//================================================================================================
  inline constexpr auto rshr = functor<rshr_t>;
//================================================================================================
//! @}
//================================================================================================
}
#  include <eve/module/core/regular/impl/rshr.hpp>

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rshr.hpp>
#endif
