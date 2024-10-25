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
#include <eve/module/core/constant/signmask.hpp>
#include <eve/module/core/regular/bit_notand.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bitofsign.hpp>

namespace eve
{
  template<typename Options>
  struct copysign_t : elementwise_callable<copysign_t, Options>
  {
    template<value T,  value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(copysign_t, copysign_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var copysign
//!   @brief `elementwise_callable` object computing the composition of a value
//!   with the magnitude of the first parameter  and the bit of sign of the second one.
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
//!      // Regular overload
//!      constexpr auto copysign(floating_value auto x, floating_value auto y)                                 noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto copysign[conditional_expr auto c](floating_value auto x, floating_value auto y)        noexcept; // 2
//!      constexpr auto copysign[logical_floating_value auto m](floating_value auto x, floating_value auto y)  noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [floating valuesl](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!       1. The value of the [elementwise](@ref glossary_elementwise) composition of a
//!          value with the magnitude of `x` and the bit of sign of `y` is returned.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/copysign)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/copysign.cpp}
//================================================================================================
  inline constexpr auto copysign = functor<copysign_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<floating_value T, floating_value U, callable_options O>
    EVE_FORCEINLINE constexpr auto copysign_(EVE_REQUIRES(cpu_), O const &, T aa, U bb) noexcept
    {
      using r_t = common_value_t<T, U>;
      r_t a = r_t(aa);
      r_t b = r_t(bb);
      return bit_or(bitofsign(b), bit_notand(signmask(eve::as(a)), a));
    }
  }
}
