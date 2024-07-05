//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct nearest_t : strict_elementwise_callable<nearest_t, Options>
  {
    template<eve::integral_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    {  return EVE_DISPATCH_CALL(v); }

    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    { return EVE_DISPATCH_CALL(v); }

    template<eve::floating_value T, only_if<signed,unsigned>  U>
    constexpr EVE_FORCEINLINE  as_integer_t<T, U> operator()(T v,  as<U> const & target) const  noexcept
    { return EVE_DISPATCH_CALL(v, target); }

    EVE_CALLABLE_OBJECT(nearest_t, nearest_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var nearest
//!   @brief  `strict_elementwise_callable` object computing the nearest integer to the input.
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
//!      constexpr auto nearest(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto nearest[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto nearest[logical_value auto m](value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!     * `x` :[value](@ref value) argument.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!     * `tol' [scalar_value](@ref value) tolerance.
//!
//!   **Return value**
//!
//!     1. the integer nearest to `x`. If `x` is an exact half-integer the rounding is made to the
//!        nearest even integer.The smallest integer not less than `x`.
//!        The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`,
//!        `FE_TOWARDZERO`. This function object implements the `FE_TONEAREST` version.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/round)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/nearest.cpp}
//! @}
//================================================================================================
  inline constexpr auto nearest = functor<nearest_t>;
}


#include <eve/module/core/regular/impl/nearest.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/nearest.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/nearest.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/nearest.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/nearest.hpp>
#endif
