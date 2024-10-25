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
  struct rsqrt_t : elementwise_callable<rsqrt_t, Options, raw_option, pedantic_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(rsqrt_t, rsqrt_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rsqrt
//!   @brief Computes the inverse of the square root of the parameter.
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
//!      constexpr auto rsqrt(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto rsqrt[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto rsqrt[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto rsqrt[raw](floating_value auto x)                     noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [real](@ref eve::floating_value) argument.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!       1. value containing the [elementwise](@ref glossary_elementwise)
//!          inverse of the square root of `x`.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!       3. call a proper system intrinsic if one exists, but with possibly
//!          very poor accuracy in return. Otherwise it uses the regular call.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/rsqrt.cpp}
//================================================================================================
  inline constexpr auto rsqrt = functor<rsqrt_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/rsqrt.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rsqrt.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/rsqrt.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rsqrt.hpp>
#endif
