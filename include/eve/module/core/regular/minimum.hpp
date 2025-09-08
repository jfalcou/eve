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
  struct minimum_t : conditional_callable<minimum_t, Options, splat_option>
  {
    template<arithmetic_value T>
    EVE_FORCEINLINE element_type_t<T> operator()(T v) const noexcept
      requires (!Options::contains(splat))
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::minimum] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v);
    }

    template<arithmetic_simd_value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept
      requires (Options::contains(splat))
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(minimum_t, minimum_);
  };

//================================================================================================
//! @addtogroup core_reduction
//! @{
//!   @var minimum
//!   @brief Computes the minimal value in a simd vector or [majorant](@ref eve::majorant) if the input is fully masked.
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
//!      element_type_t<T> minimum(T v) requires(!O::contains(splat))                noexcept; // 1
//!
//!      template<arithmetic_simd_value T>
//!      T minimum(T v) requires(O::contains(splat))                                 noexcept; // 2
//!
//!      // Lanes masking
//!      auto minimum[conditional_expr auto c](/*any of the above overloads*/)       noexcept; // 3
//!      auto minimum[logical_value auto m](/*any of the above overloads*/)          noexcept; // 3
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
//!     1. The minimal value of all lanes. Scalar values are returned as is.
//!     2. The minimal value of all lanes splatted across every lane of said input.
//!     3. Same as the above but the masked lanes are ignored during the operation.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/minimum.cpp}
//================================================================================================
  inline constexpr auto minimum = functor<minimum_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/minimum.hpp>

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/minimum.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/minimum.hpp>
#endif
