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
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fnma.hpp>


namespace eve
{
  template<typename Options>
  struct lerp_t : elementwise_callable<lerp_t, Options, pedantic_option>
  {
    template<value T,  value U,  value V>
    requires(eve::same_lanes_or_scalar<T, U, V>)
    constexpr EVE_FORCEINLINE common_value_t<T, U, V> operator()(T a, U b, V c) const
    { return EVE_DISPATCH_CALL(a, b, c); }

    EVE_CALLABLE_OBJECT(lerp_t, lerp_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var lerp
//!   @brief Computes the  linear interpolation.
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
//!      constexpr auto lerp(floating_value auto x, floating_value auto y, floating_value auto t)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto lerp[conditional_expr auto c](floating_value auto x, floating_value auto y, floating_value auto t) noexcept; // 2
//!      constexpr auto lerp[logical_value auto m](floating_value auto x, floating_value auto y, floating_value auto t)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto abs[pedantic](floating_value auto x, floating_value auto y, floating_value auto t)                 noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `t`: [floating](@ref eve::floating_value) arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the interpolation (or extrapolation)  between `x` and `y` is returned.
//!         The call is semantically equivalent to `x+t*(y-x)` but uses fma opportunities.
//!      2. [The operation is performed conditionnaly](@ref conditional)
//!      3. `pedantic` version of fma is used internally.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/lerp.cpp}
//================================================================================================
  inline constexpr auto lerp = functor<lerp_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    lerp_(EVE_REQUIRES(cpu_), O const & o, T const &a,  T const &b,  T const &t) noexcept
    {
      return fma[o](t, b, fnma[o](t, a, a));
    }
  }
}
