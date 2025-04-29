//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<typename Options>
  struct sum_t : conditional_callable<sum_t, Options, splat_option>
  {
    template<arithmetic_value T>
    EVE_FORCEINLINE element_type_t<T> operator()(T v) const noexcept
      requires (!Options::contains(splat2))
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::sum] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v);
    }

    template<arithmetic_simd_value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept
      requires (Options::contains(splat2))
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(sum_t, sum_);
  };

  //================================================================================================
  //! @addtogroup core_reduction
  //! @{
  //!   @var sum
  //!   @brief Computes the horizontal sum of the lanes values of an
  //!          [arithmetic_simd_value](@ref eve::arithmetic_simd_value).
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
  //!      template<arithmetic_value T>
  //!      element_type_t<T> sum(T v) requires(!O::contains(splat))                noexcept; // 1
  //!
  //!      template<arithmetic_simd_value T>
  //!      T sum(T v) requires(O::contains(splat))                                 noexcept; // 2
  //!
  //!      // Lanes masking
  //!      auto sum[conditional_expr auto c](/*any of the above overloads*/)       noexcept; // 3
  //!      auto sum[logical_value auto m](/*any of the above overloads*/)          noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //!   **Parameter**
  //!
  //!     * `v`: [argument](@ref eve::arithmetic_value).
  //!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. The sum of all values in the input. Scalar values are returned as is.
  //!     2. The sum of all values in the input splatted across every lane of said input.
  //!     3. Same as the above but the masked lanes are ignored during the operation.
  //================================================================================================
  inline constexpr auto sum = functor<sum_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/detail/function/simd/common/sum.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/sum.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/detail/function/simd/arm/neon/sum.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/sum.hpp>
#endif
