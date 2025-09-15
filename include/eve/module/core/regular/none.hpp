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

namespace eve
{
  template<typename Options>
  struct none_t : conditional_callable<none_t, Options, splat_option>
  {
    template<relaxed_logical_value T>
    EVE_FORCEINLINE bool operator()(T v) const noexcept
      requires (!Options::contains(splat))
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
         "[eve::none] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v);
    }

    template<logical_simd_value T>
    EVE_FORCEINLINE bool operator()(top_bits<T> v) const noexcept
      requires (!Options::contains(splat))
    {
      return EVE_DISPATCH_CALL(v);
    }

    template<logical_simd_value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept
      requires (Options::contains(splat))
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(none_t, none_);
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
  //!      bool none(T v) requires !Options::contains(splat)                    noexcept; // 1
  //!
  //!      template<logical_simd_value T>
  //!      bool none(top_bits<T> t) requires !Options::contains(splat)          noexcept; // 1
  //!
  //!      // Splat overload
  //!      template<logical_simd_value T>
  //!      bool none(T t) requires Options::contains(splat)                     noexcept; // 2
  //!
  //!      // Lanes masking
  //!      bool none[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
  //!      bool none[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
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
  //!      2. The result of the reduction is splatted across every lane of the output.
  //!      3. Same as the above but the masked lanes are ignored during the operation.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/none.cpp}
  //================================================================================================
  inline constexpr auto none = functor<none_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/none.hpp>

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/none.hpp>
#endif
