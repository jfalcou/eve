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
#include <eve/module/special/regular/lambert.hpp>

namespace eve
{
  template<typename Options>
  struct omega_t : elementwise_callable<omega_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(omega_t, omega_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var omega
//!   @brief Computes the Wright \f$\omega\f$ the inverse function of \f$ x \rightarrow \log
//!   x+x\f$
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
//!      constexpr auto omega(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto omega[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto omega[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating_value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the Wright \f$\omega\f$ function is returne
//!        (the inverse function of \f$ x \rightarrow \log x+x\f$) is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Wright omega function](https://en.wikipedia.org/wiki/Wright_omega_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/special/omega.cpp}
//================================================================================================
  inline constexpr auto omega = functor<omega_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T
    omega_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      auto br_pos = [](auto xx){
        auto xx0     = if_else(xx > 1, xx, -eve::log(eve::abs(xx)) + eps(as(xx)));
        xx0          = if_else(is_nan(xx), xx, xx0);
        int maxiter = 100;
        for( int i = 0; i <= maxiter; ++i )
        {
          auto dxx0  = xx0 * (log(xx0) + xx0 - xx) / inc(xx0);
          auto test = is_not_greater(eve::abs(dxx0), 2 * eps(as(xx)) * eve::max(xx, one(as(xx))));
          if( eve::all(test) ) break;
          xx0 = eve::max(eve::smallestposval(as(xx0)), xx0 - if_else(test, zero, dxx0));
        }
        return xx0;
      };

      auto br_neg = [](auto xx){
        auto [w0, wm1] = lambert(exp(xx));
        return w0;
      };
      auto r       = nan(as<T>()); // nan case treated here
      r            = if_else(x == one(as(x)), one, r);
      r            = if_else(x == inf(as(x)), inf(as(x)), r);
      r            = if_else(x == zero(as(x)), T(0.56714329040978384011), r);
      auto notdone = is_nan(r);
      if( eve::any(notdone) )
      {
        notdone = next_interval(br_pos, notdone, x >= one(as(x)), r, x);
        if( eve::any(notdone) ) { notdone = last_interval(br_neg, notdone, r, x); }
      }
      return r;
    }
  }
}
