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
    template<eve::floating_value T0, eve::floating_value T1>
    requires (same_lanes_or_scalar<T0, T1>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ellint_rc_t, ellint_rc_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_rc
//!   @brief  `elementwise_callable` object computing the degenerate Carlson's elliptic integral
//!   \f$  \mathbf{R}_\mathbf{C}(x, y) = \frac12 \int_{0}^{\infty}
//!   \scriptstyle(t+x)^{-1/2}(t+y)^{-1}\scriptstyle\;\mathrm{d}t\f$.
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      constexpr auto ellint_1(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto ellint_1[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto ellint_1[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [floating valuess](@ref floating_value). `x` and `y` must be
//!                 strictly positive and `y` non zero or the result is `NaN`.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. the value of the Carlson degenerate elliptic integral:
//!       \f$\mathbf{R}_\mathbf{C}(x, y) = \frac12 \int_{0}^{\infty}
//!       \scriptstyle(t+x)^{-1/2}(t+y)^{-1}\scriptstyle\;\mathrm{d}t\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{External references}
//!   *  [DLMF: Elliptic Integrals](https://dlmf.nist.gov/19.2)
//!   *  [Wolfram MathWorld: Elliptic Integral](https://mathworld.wolfram.com/CarlsonEllipticIntegrals.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/ellint_rc.cpp}
//================================================================================================
  inline constexpr auto ellint_rc = functor<ellint_rc_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr auto ellint_rc_(EVE_REQUIRES(cpu_), O const&, T x, T y) noexcept
    {
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
        auto br_0 = [tmp0](auto xx, auto yy) // xx == yy || xx == 0
          {
            auto z = mul[is_eqz(xx)](tmp0, pio_2(as(yy)));
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
              auto br_3 = [tmp0, tmp1](auto xx) { return log((sqrt(xx) + tmp1) * tmp0) / tmp1; };
              last_interval(br_3, notdone, r, x);
            }
          }
        }
      }
      return if_else(x == inf(as(x)), zero, r * prefix);
    }
  }
}
