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
#include <eve/module/elliptic/ellint_rd.hpp>
#include <eve/module/elliptic/ellint_rf.hpp>
#include <eve/module/math.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
  template<typename Options>
  struct ellint_rg_t : elementwise_callable<ellint_rg_t, Options, raw_option>
  {
    template<floating_value T0, floating_value T1, floating_value T2>
    constexpr EVE_FORCEINLINE common_value_t<T0, T1, T2> operator()(T0 a, T1 b, T2 c) const noexcept
      requires (same_lanes_or_scalar<T0, T1, T2>)
    {
      return this->behavior(as<common_value_t<T0, T1, T2>>{}, eve::current_api, this->options(), a, b, c);
    }

    EVE_CALLABLE_OBJECT(ellint_rg_t, ellint_rg_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_rg
//!   @brief Computes the Carlson's elliptic integral
//!   \f$ \mathbf{R}_\mathbf{G}(x, y) = \frac1{4\pi} \int_{0}^{2\pi}\int_{0}^{\pi}
//!   \scriptstyle\sqrt{x\sin^2\theta\cos^2\phi
//!   +y\sin^2\theta\sin^2\phi
//!   +z\cos^2\theta} \scriptstyle\;\mathrm{d}\theta\;\mathrm{d}\phi\f$
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
//!      constexpr auto ellint_rg(floating_value auto x, floating_value auto y, floating_value auto z)   noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto ellint_rg[conditional_expr auto c](floating_value auto x, floating_value auto y,
//!                                                        floating_value auto z)                        noexcept; // 2
//!      constexpr auto ellint_rg[logical_value auto m](floating_value auto x, floating_value auto y,
//!                                                     floating_value auto z)                           noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`:  [floating real arguments](@ref eve::floating_value).
//!                       All arguments must be non-negative or the result is nan.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. the value of the \f$\mathbf{R}_\mathbf{G}\f$ Carlson elliptic integral:
//!       \f$\frac1{4\pi} \int_{0}^{2\pi}\int_{0}^{\pi}
//!       \scriptstyle\sqrt{x\sin^2\theta\cos^2\phi
//!       +y\sin^2\theta\sin^2\phi
//!       +z\cos^2\theta} \scriptstyle\;\mathrm{d}\theta\;\mathrm{d}\phi\f$ is returned:
//!     2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{External references}
//!   *  [DLMF: Elliptic Integrals](https://dlmf.nist.gov/19.2)
//!   *  [Wolfram MathWorld: Elliptic Integral](https://mathworld.wolfram.com/CarlsonEllipticIntegrals.html)
//!
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/ellint_rg.cpp}
//================================================================================================
  inline constexpr auto ellint_rg = functor<ellint_rg_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T ellint_rg_(EVE_REQUIRES(cpu_), O const&, T x, T y, T z)
    {
      if constexpr(O::contains(raw))
      {
        swap_if(x < y, x, y);
        swap_if(x < z, x, z);
        swap_if(y > z, y, z);
        // now all(x >= z) and all(z >= y)
        return average(z*ellint_rf(x,y,z)-(x-z)*(y-z)*ellint_rd(x, y, z)*third(as<T>()), sqrt(x*y/z));
      }
      else
      {
        auto r       = nan(as(x));
        auto notdone = is_nltz(x) && is_nltz(y) && is_nltz(z);
        // any parameter nan or less than zero implies nan
        auto br0 = [x, y, z]() { return ellint_rg[raw](x, y, z); };
        last_interval(br0, notdone, r);
        return r;
      }
    }
  }
}
