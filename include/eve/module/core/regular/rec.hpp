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
struct rec_t : elementwise_callable<rec_t, Options, raw_option, pedantic_option,
                                    lower_option, upper_option, strict_option>
{
  template<value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
  {
    return EVE_DISPATCH_CALL_PT(T, v);
  }

  EVE_CALLABLE_OBJECT(rec_t, rec_);
};

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rec
//!   @brief Computes the inverse of the parameter.
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
//!      constexpr auto rec(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto rec[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto rec[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto rec[raw](value auto x)                     noexcept; // 3
//!      constexpr auto rec[pedantic](value auto x)                noexcept; // 4
//!      constexpr auto rec[lower](floating_value auto x)          noexcept; // 5
//!      constexpr auto rec[upper](floating_value auto x)          noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [real](@ref eve::value) argument.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the inverse of `x` is returned but does not take care of denormals.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. call a proper system intrinsic if one exists, but with possibly
//!         very poor accuracy in return (circa 12 bits). Otherwise it uses the regular call.
//!      4. equivalent to the division operation of `one(as(x))` by `x`.
//!      5. The inverse is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!         to be less or equal to the exact one (except for Nans).
//!      6. The inverse is computed  in a 'round toward \f$\infty\f$ mode. The result is guaranted
//!        to be greater or equal to the exact one (except for Nans).
//!
//!  @note
//!     For [integral value](@ref integral_value) `rec(x)` is equivalent to:
//!       * If x==1 or x==-1, x is returned.
//!       * If x==0,  [the greatest representable positive value](@ref eve::valmax) is returned.
//!       * Otherwise 0 is returned.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/rec.cpp}
//================================================================================================
  inline constexpr auto rec = functor<rec_t>;
//================================================================================================
//! @}
//================================================================================================
}


#include <eve/module/core/regular/impl/rec.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rec.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/rec.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rec.hpp>
#endif
