//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Options>
  struct first_true_t : conditional_callable<first_true_t, Options>
  {
    template<relaxed_logical_value T>
    constexpr EVE_FORCEINLINE std::optional<std::ptrdiff_t> operator()(T v) const noexcept
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::first_true] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v);
    }

    template<logical_simd_value T>
    constexpr EVE_FORCEINLINE std::optional<std::ptrdiff_t> operator()(top_bits<T> v) const noexcept
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::first_true] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(first_true_t, first_true_);
  };

  //================================================================================================
  //! @addtogroup core_reduction
  //! @{
  //!   @var first_true
  //!   @brief Returns the index of the first true element in a logical value if there is one.
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   ## Should you check for any?
  //!
  //!   The function is considering the case when nothing is set to be likely,
  //!   checking for eve::any before hand is not going to be helpful.
  //!   At the moment there isn't a function that would do it otherwise.
  //!
  //!   ## What if I know there is a match?
  //!   We would recommend `*eve::first_true(m)` - this is likely to trigger
  //!   compiler optimizations, based on it being UB otherwise.
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   template <relaxed_logical_value L>
  //!   std::optional<std::ptrdiff_t> first_true(L m);                                                                  // 1
  //!
  //!   template <logical_simd_value L>
  //!   std::optional<std::ptrdiff_t> first_true(top_bits<L> m);                                                        // 1
  //!
  //!   // lane masking
  //!   constexpr std::optional<std::ptrdiff_t> first_true[conditional_expr auto c](/* any of the above */) noexcept;   // 1
  //!   constexpr std::optional<std::ptrdiff_t> first_true[logical_value auto c](/* any of the above */) noexcept;      // 1
  //!
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * m - logical_value or top_bits where to find first true value
  //!
  //!   **Return value**
  //!
  //!    1. An `std::optional` containing the index of the first non-zero element, `std::nullopt` if there are none.
  //!    2. Same as 1. but lanes masked by the condition are ignored during the search.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/first_true.cpp}
  //!
  //================================================================================================
  inline constexpr auto first_true = functor<first_true_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/first_true.hpp>

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/first_true.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/first_true.hpp>
#endif
