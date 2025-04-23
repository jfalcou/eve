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
  struct last_true_t : conditional_callable<last_true_t, Options>
  {
    template<relaxed_logical_value T>
    EVE_FORCEINLINE std::optional<std::ptrdiff_t> operator()(T v) const noexcept
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::last_true] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v);
    }

    template<logical_simd_value T>
    EVE_FORCEINLINE std::optional<std::ptrdiff_t> operator()(top_bits<T> v) const noexcept
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(last_true_t, last_true_);
  };

  //================================================================================================
  //! @addtogroup core_reduction
  //! @{
  //!   @var last_true
  //!   @brief Returns the index of the last element in the input which evaluates to `true`, if there is one.
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   template <relaxed_logical_value L>
  //!   std::optional<std::ptrdiff_t> last_true(L m) noexcept;                                               // 1
  //!
  //!   template <logical_simd_value L>
  //!   std::optional<std::ptrdiff_t> last_true(top_bits<L> m) noexcept;                                     // 1
  //!
  //!   // lane masking
  //!   std::optional<std::ptrdiff_t> last_true[conditional_expr auto c](/* any of the above */) noexcept;   // 2
  //!   std::optional<std::ptrdiff_t> last_true[logical_value auto c](/* any of the above */) noexcept;      // 2
  //!
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * m - logical_value or top_bits where to find last true value
  //!
  //!   **Return value**
  //!
  //!    1. An `std::optional` containing the index of the last element which evaluates to `true`,
  //!       `std::nullopt` if there are none.
  //!    2. Same as 1. but masked elements are ignored during the search.
  //!
  //!   ## Should you check for any?
  //!
  //!   The function is considering the case when nothing is set to be likely,
  //!   checking for eve::any before hand is not going to be helpful.
  //!   At the moment there isn't a function that would do it otherwise.
  //!
  //!   ## What if I know there is a match?
  //!   We would recommend `*eve::last_true(m)` - this is likely to trigger
  //!   compiler optimizations, based on it being UB otherwise.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/last_true.cpp}
  //================================================================================================
  inline constexpr auto last_true = functor<last_true_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/last_true.hpp>

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/last_true.hpp>
#endif
