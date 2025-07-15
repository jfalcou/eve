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
  struct maximum_t : conditional_callable<maximum_t, Options, splat_option>
  {
    template<arithmetic_value T>
    EVE_FORCEINLINE element_type_t<T> operator()(T v) const noexcept
      requires (!Options::contains(splat2))
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::maximum] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v);
    }

    template<arithmetic_simd_value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept
      requires (Options::contains(splat2))
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(maximum_t, maximum_);
  };

  //================================================================================================
  //! @addtogroup core_reduction
  //! @{
  //!   @var maximum
  //!   @brief Computes the maximal value in a simd vector
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
  //!      template <arithmetic_value T>
  //!      element_type_t<T> maximum(T x) requires(!O::contains(splat))            noexcept; // 1
  //!
  //!      template <arithmetic_simd_value T>
  //!      T maximum(T x) requires(O::contains(splat))                             noexcept; // 2
  //!
  //!      // Lanes masking
  //!      auto maximum[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
  //!      auto maximum[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: [argument](@ref eve::value).
  //!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. The maximal value of all lanes. Scalar values are returned as is.
  //!     2. The maximal value of all lanes splatted across every lane of the input.
  //!     3. Same as the above but the masked lanes are ignored during the operation.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/maximum.cpp}
  //================================================================================================
  inline constexpr auto maximum = functor<maximum_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/maximum.hpp>

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/maximum.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/maximum.hpp>
#endif
