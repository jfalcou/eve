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
#include <eve/module/core/regular/bit_shl.hpp>

namespace eve
{
  template<typename Options>
  struct bit_set_t : strict_elementwise_callable<bit_set_t, Options>
  {
    template<eve::integral_value T, integral_value I >
    constexpr EVE_FORCEINLINE T operator()(T v, I i) const
    { return EVE_DISPATCH_CALL(v, i); }

    EVE_CALLABLE_OBJECT(bit_set_t, bit_set_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_set
//!   @brief  `strict_elementwise_callable` object setting to 1 the ith bit of each element.
///!
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
//!      constexpr auto bit_set(integral_value auto x, integral_value auto n)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_set[conditional_expr auto c](integral_value, auto x integral_value auto n) noexcept; // 2
//!      constexpr auto bit_set[logical_value auto m](integral_value auto x, integral_value auto n)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::integral_value).
//!     * `i`: index to set
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!      1. The value of the parameter is returned with the ith bit set to 1.
//!         If the index is out of range the call will assert.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_set.cpp}
//================================================================================================
  inline constexpr auto bit_set = functor<bit_set_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, typename I, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_set_(EVE_REQUIRES(cpu_), O const&, T a, I i) noexcept
    {
      [[maybe_unused]] constexpr std::ptrdiff_t S8 = sizeof(element_type_t<T>)*8;
      EVE_ASSERT(eve::all(i >= 0 && i < S8), "index is out or range");
      return bit_or(a, bit_shl(one(as(a)), i));
    }
  }
}
