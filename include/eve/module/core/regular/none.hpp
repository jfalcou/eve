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
    EVE_FORCEINLINE bool operator()(T v) const noexcept
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
         "[eve::none] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return !any[this->options()[condition_key]](v);
    }

    template<logical_simd_value T>
    EVE_FORCEINLINE bool operator()(top_bits<T> v) const noexcept
    {
      return !any[this->options()[condition_key]](v);
    }
  };

  //================================================================================================
  //! @addtogroup core_reduction
  //! @{
  //!   @var none
  //!   @brief Computes a bool value which is true if and only if all elements of `x` evaluate to false.
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
  //!      template <relaxed_logical_value T>
  //!      bool none(T v)                                                       noexcept; // 1
  //!
  //!      template<logical_simd_value T>
  //!      bool none(top_bits<T> t)                                             noexcept; // 1
  //!
  //!      // Lanes masking
  //!      bool none[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
  //!      bool none[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `v`: [argument](@ref eve::relaxed_logical_value).
  //!     * `t`: [top bits](@ref top_bits).
  //!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
  //!
  //!   **Return value**
  //!
  //!      1. A bool value which is true if and only if all elements of `x` evaluates to false.
  //!      2. A bool value which is true if and only if all retained elements of `x` evaluates to false.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/none.cpp}
  //================================================================================================
  inline constexpr auto none = functor<none_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}
