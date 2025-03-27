/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Options>
  struct count_true_t : conditional_callable<count_true_t, Options>
  {
    template<relaxed_logical_value T>
    constexpr EVE_FORCEINLINE std::ptrdiff_t operator()(T v) const noexcept
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::count_true] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v);
    }

    template<logical_simd_value T>
    constexpr EVE_FORCEINLINE std::ptrdiff_t operator()(top_bits<T> v) const noexcept
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::count_true] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(count_true_t, count_true_);
  };

  //================================================================================================
  //! @addtogroup core_reduction
  //! @{
  //!   @var count_true
  //!   @brief Computes the number of non-zero elements
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
  //!      constexpr std::ptrdiff_t count_true(relaxed_logical_value auto x)                              noexcept; // 1
  //!      constexpr std::ptrdiff_t count_true(top_bits auto t)                                           noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr std::ptrdiff_t count_true[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
  //!      constexpr std::ptrdiff_t count_true[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
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
  //!      1. The number of non-zero elements in `x`. If `x` is a scalar, then it is treated as one element.
  //!      2. The masked version which return the number of non-masked non-zero elements.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/count_true.cpp}
  //!  @groupheader{Semantic Modifiers}
  //!
  //================================================================================================
  inline constexpr auto count_true = functor<count_true_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/count_true.hpp>

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/count_true.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/module/core/regular/impl/simd/riscv/count_true.hpp>
#endif
