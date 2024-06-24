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
  struct bit_unset_t : strict_elementwise_callable<bit_unset_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    template<eve::value T, integral_scalar_value I >
    constexpr EVE_FORCEINLINE T operator()(T v, I i) const
    { return EVE_DISPATCH_CALL(v, i); }

    EVE_CALLABLE_OBJECT(bit_unset_t, bit_unset_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_unset
//!   @brief  `strict_elementwise_callable` object setting to 01 the ith bit of each element.
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
//!      constexpr auto bit_unset(unsigned_value auto x integral_scalar_value n) noexcept;             // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_unset[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
//!      constexpr auto bit_unset[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [argument](@ref eve::value).
//!     * `i`:  index to unset
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!       1. The value of the parameter is returned with the ith bit set to 0
//!          if the index is out of range the call will assert.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_unset.cpp}
//! @}
//================================================================================================
  inline constexpr auto bit_unset = functor<bit_unset_t>;

  namespace detail
  {
    template<typename T, typename I, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_unset_(EVE_REQUIRES(cpu_), O const&, T a, I i) noexcept
    {
      [[maybe_unused]] constexpr std::ptrdiff_t S8 = sizeof(element_type_t<T>)*8;
      EVE_ASSERT(eve::all(i >= 0 && i < S8), "some index elements are out or range");
      return bit_andnot(a, bit_shl(one(as(a)), i));
    }
  }
}
