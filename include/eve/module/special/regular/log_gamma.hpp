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
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct log_gamma_t : elementwise_callable<log_gamma_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(log_gamma_t, log_gamma_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var log_gamma
//!   @brief `elementwise_callable` object computing the natural logarithm of the \f$\Gamma\f$ function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto log_gamma(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto log_gamma[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto log_gamma[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [strictly positive real floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. The value of the  logarithm of the \f$\Gamma\f$ function is returned.
//!         this callable returns NaN if `eve::gamma(x)` is less than zero.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Log Gamma Function](https://mathworld.wolfram.com/LogGammaFunction.html
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/log_gamma.cpp}
//================================================================================================
  inline constexpr auto log_gamma = functor<log_gamma_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<typename T, callable_options O>
    constexpr T
    log_gamma_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      auto aa0 = if_else(a0 == minf(as(a0)) || is_lez(signgam(a0)) ||(is_ltz(a0) && is_flint(a0)), allbits, a0);
      return log_abs_gamma(aa0);
    }
  }
}
