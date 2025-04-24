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
  struct all_t : conditional_callable<all_t, Options>
  {
    template<relaxed_logical_value T>
    constexpr EVE_FORCEINLINE bool operator()(T v) const
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::all] - Cannot use a relative conditional expression or a simd value to mask a scalar value");
      
      return EVE_DISPATCH_CALL(v);
    }

    template<logical_simd_value T>
    constexpr EVE_FORCEINLINE bool operator()(top_bits<T> v) const noexcept
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(all_t, all_);
  };

  //================================================================================================
  //! @addtogroup core_reduction
  //! @{
  //!   @var all
  //!   @brief Computes a bool value which is true if and only if every elements of `x` evaluates to true.
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
  //!      template <relaxed_logical_value L>
  //!      constexpr bool all(L x)                                                       noexcept; // 1
  //!
  //!      template <logical_simd_value L>
  //!      constexpr bool all(top_bits<L> t)                                             noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr bool all[conditional_expr auto c](/* any of the above overloads */) noexcept; // 2
  //!      constexpr bool all[logical_value auto m](/* any of the above overloads */)    noexcept; // 2
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
  //!      1. A bool value which is true if and only if every elements of `x` evaluates to true.
  //!      2. A masked version which ignores the masked elements during the search.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/all.cpp}
  //================================================================================================
  inline constexpr auto all = functor<all_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/all.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/all.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/all.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/all.hpp>
#endif
