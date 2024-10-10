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
#include <eve/module/core/regular/rem.hpp>

namespace eve
{
  template<typename Options>
  struct remainder_t : elementwise_callable<remainder_t, Options>
  {
    template<floating_value T0, floating_value T1>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 t0, T1 t1) const noexcept
      requires (same_lanes_or_scalar<T0, T1>)
    {
      return this->behavior(as<common_value_t<T0, T1>>{}, eve::current_api, this->options(), t0, t1);
    }

    EVE_CALLABLE_OBJECT(remainder_t, remainder_);
  };


//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fmod
//!   @brief mimick the std::remainder function for floating values.
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
//!      constexpr auto remainder(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto remainder[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto remainder[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:   [real](@ref eve::value) arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. Returns the remainder after division division of `x` by `y` and is
//!         equivalent to  `x- eve::nearest(eve:div(x, y))*y`. In particular:
//!        * If `x` is \f$\pm\inf\f$ or `NaN`, `NaN` is returned.
//!        * If `y` is \f$\pm0\f$  \f$\pm0\f$ is returned
//!        * If `y` is `NaN`, `NaN` is returned.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/remainder.cpp}
//================================================================================================
  inline constexpr auto remainder = functor<remainder_t>;
//================================================================================================
///! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr auto
    remainder_(EVE_REQUIRES(cpu_), O const&, T const& a, T const& b) noexcept
    {
      return rem[to_nearest](a, b);
    }
  }
}
