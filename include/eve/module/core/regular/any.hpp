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
   struct any_t : relative_conditional_callable<any_t, Options>
   {
     template<relaxed_logical_value T>
    EVE_FORCEINLINE bool operator()(T v) const noexcept
     {
       static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
         "[eve::any] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

       return EVE_DISPATCH_CALL(v);
     }

     template<logical_simd_value T>
    EVE_FORCEINLINE bool operator()(top_bits<T> v) const noexcept
     {
       return EVE_DISPATCH_CALL(v);
     }

     EVE_CALLABLE_OBJECT(any_t, any_);
   };

  //================================================================================================
  //! @addtogroup core_reduction
  //! @{
  //!   @var any
  //!   @brief Computes a bool value which is true if and only if one or more elements of `x`
  //!          evaluates to true.
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
  //!      bool any(T v)                                                          noexcept; // 1
  //!
  //!      template <logical_simd_value T>
  //!      bool any(top_bits<T> v)                                                noexcept; // 1
  //!
  //!      // Lanes masking
  //!      bool any[conditional_expr auto c](/* any of the above overloads */)    noexcept; // 2
  //!      bool any[logical_value auto m](/* any of the above overloads */)       noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `v`: [argument](@ref eve::value).
  //!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.qq
  //!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. A bool value which is true if and only if one or more elements of `x` evaluates
  //!        to true.
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/any.cpp}
  //================================================================================================
  inline constexpr auto any = functor<any_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/any.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/any.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/any.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/any.hpp>
#endif
