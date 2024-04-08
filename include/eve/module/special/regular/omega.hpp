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
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(omega_t, omega_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var omega
//!   @brief Computes the the Wright \f$\omega\f$ the inverse function of \f$ x \rightarrow \log
//!   x+x\f$
//!
//!   **Defined in header**
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
//!      template< eve::floating_ordered_value T >
//!      T omega(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the Wright \f$\omega\f$ function is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/omega.cpp}
//! @}
//================================================================================================
inline constexpr auto omega = functor<omega_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T
    omega_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      auto br_pos = [](auto x){
        auto x0     = if_else(x > 1, x, -eve::log(eve::abs(x)) + eps(as(x)));
        x0          = if_else(is_nan(x), x, x0);
        int maxiter = 100;
        for( int i = 0; i <= maxiter; ++i )
        {
          auto dx0  = x0 * (log(x0) + x0 - x) / inc(x0);
          auto test = is_not_greater(eve::abs(dx0), 2 * eps(as(x)) * eve::max(x, one(as(x))));
          if( eve::all(test) ) break;
          x0 = eve::max(eve::smallestposval(as(x0)), x0 - if_else(test, zero, dx0));
        }
        return x0;
      };

      auto br_neg = [](auto x){
        auto [w0, wm1] = lambert(exp(x));
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
