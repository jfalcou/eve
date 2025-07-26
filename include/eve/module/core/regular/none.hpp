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
#include <eve/module/core/regular/any.hpp>

namespace eve
{
  template<typename Options>
  struct none_t : strict_elementwise_callable<none_t, Options>
  {
    template<relaxed_logical_value T>
    constexpr EVE_FORCEINLINE bool operator()(T v) const noexcept
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
         "[eve::none] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return !any[this->options()[condition_key]](v);
    }

    template<logical_simd_value T>
    constexpr EVE_FORCEINLINE bool operator()(top_bits<T> v) const noexcept
    {
      return !any[this->options()[condition_key]](v);
    }
  };

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
  //!     * `x`: [argument](@ref eve::logical_value).
  //!     * `t`: [top bits](@ref top_bits).
  //!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
  //!
  //!   **Return value**
  //!
  //!      1. A bool value which is true if and only if all elements of `x` are zero.
  //!      2. A bool value which is true if and only if all retained elements of `x` are zero.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/none.cpp}
  //================================================================================================
  inline constexpr auto none = functor<none_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}
