//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct logical_and_t : elementwise_callable<logical_and_t, Options>
  {
    template<typename T, typename U>
    constexpr EVE_FORCEINLINE common_logical_t<T, U> operator()(T a, U b) const noexcept
      requires (same_lanes_or_scalar<T, U> && relaxed_logical_value<T> && relaxed_logical_value<U>)
    {
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(logical_and_t, logical_and_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_and
//!   @brief `strict_elementwise_callable` computing the logical AND of its arguments.
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
//!      constexpr auto logical_and(auto logical_value x, auto logical_value y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [logical arguments](@ref eve::logical_value).
//!
//!    **Return value**
//!
//!     Returns the logical AND of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_and(x, y)` is semantically equivalent to `x && y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and does not shortcut.
//!
//!    @note
//!      Although the infix notation with `&&` is supported, the `&&` operator on
//!      standard scalar types is the original one and so will return bool instead of
//!      eve::logical_value.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/logical_and.cpp}
//================================================================================================
  inline constexpr auto logical_and = functor<logical_and_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/logical_and.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/logical_and.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/logical_and.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/module/core/regular/impl/simd/riscv/logical_and.hpp>
#endif
