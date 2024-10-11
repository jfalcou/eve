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
  struct sqrt_t : elementwise_callable<sqrt_t, Options, raw_option,
                                       lower_option, upper_option, strict_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(sqrt_t, sqrt_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sqrt
//!   @brief Computes the square root of the parameter.
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
//!      constexpr auto sqrt(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sqrt[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sqrt[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sqrt[raw](floating_value auto x)                     noexcept; // 3
//!      constexpr auto sqrt[lower](floating_value auto x)                   noexcept; // 4
//!      constexpr auto sqrt[upper](floating_value auto x)                   noexcept; // 5
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::floating_value) argument.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. floating value containing the [elementwise](@ref glossary_elementwise)
//!        square root of `x` or Nan if `x` is less than zero.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. call a proper system intrinsic if one exists, but with possibly
//!        very poor accuracy in return. Otherwise it uses the regular call
//!     4. The square root is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!      to be less or equal to the exact one (except for Nans).
//!     5. The square root is computed  in a 'round toward \f$\infty\f$ mode. The result is guaranted
//!       to be greater or equal to the exact one (except for Nans).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sqrt.cpp}
//================================================================================================
  inline constexpr auto sqrt = functor<sqrt_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/sqrt.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/sqrt.hpp>
#endif
