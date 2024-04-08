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
#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
  template<typename Options>
  struct ellint_rc_t : elementwise_callable<ellint_rc_t, Options>
  {
    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1>
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ellint_rc_t, ellint_rc_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_rc
//!   @brief computes the degenerate Carlson's elliptic integral
//!   \f$  \mathbf{R}_\mathbf{C}(x, y) = \frac12 \int_{0}^{\infty}
//!   \scriptstyle(t+x)^{-1/2}(t+y)^{-1}\scriptstyle\;\mathrm{d}t\f$.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/elliptic.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      constexpr template< eve::floating_ordered_value T,  eve::floating_ordered_value U >
//!      eve::common_value_t<T, U> ellint_rc(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [floating real arguments](@ref eve::floating_ordered_value). `x` and `y` must be
//!                 strictly positive and `y` non zero or the result is NaN.
//!
//!   **Return value**
//!
//!    the value of the \f$\mathbf{R}_\mathbf{C}\f$ elliptic integral is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_rc.cpp}
//! @}
//================================================================================================
  inline constexpr auto ellint_rc = functor<ellint_rc_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    constexpr common_value_t<T, U>
    ellint_rc_(EVE_REQUIRES(cpu_), O const&, T xx, U yy) noexcept
    {
      using r_t = common_value_t<T, U>;
      r_t x = r_t(xx);
      r_t y = r_t(yy);
      auto ylt0   = is_ltz(y);
      auto prefix = one(as(x));
      if( eve::any(ylt0) ) // provisions for y < 0
      {
        prefix = if_else(ylt0, sqrt(x / (x - y)), one);
        x      = sub[ylt0](x, y);
        y      = if_else(ylt0, -y, y);
      }
      // now all y are >= 0
      auto r       = nan(as(x));
      auto notdone = is_nltz(x) && is_nez(y);
      if( eve::any(notdone) )
      {
        auto tmp0 = rsqrt(y);
        auto br_0 = [tmp0](auto x, auto y) // x == y || x == 0
          {
            auto z = mul[is_eqz(x)](tmp0, pio_2(as(y)));
            return z; // if_else(x == y, tmp0, tmp0*pio_2(as(y)));
          };
        notdone = next_interval(br_0, notdone, (x == y) || is_eqz(x), r, x, y);
        if( eve::any(notdone) )
        {
          auto tmp1 = sqrt(eve::abs(x - y));
          auto tmp2 = rsqrt(x);
          auto tmp3 = tmp1 * tmp2;
          auto br_1 = [tmp1, tmp3]() // y >  x
            { return atan(tmp3) / tmp1; };
          notdone = next_interval(br_1, notdone, y > x, r);
          if( eve::any(notdone) )
          {
            auto br_2 = [tmp1, tmp3]() // y > 0.5*x
              { return atanh(tmp3) / tmp1; };
            notdone = next_interval(br_2, notdone, y > T(0.5) * x, r);
            if( eve::any(notdone) )
            {
              auto br_3 = [tmp0, tmp1](auto x) { return log((sqrt(x) + tmp1) * tmp0) / tmp1; };
              last_interval(br_3, notdone, r, x);
            }
          }
        }
      }
      return if_else(x == inf(as(x)), zero, r * prefix);
    }
  }
}
