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
  struct ellint_rf_t : elementwise_callable<ellint_rf_t, Options, raw_option>
  {
     template<eve::floating_ordered_value T0, eve::floating_ordered_value T1, eve::floating_ordered_value T2>
     requires (same_lanes_or_scalar<T0, T1, T2>)
     constexpr EVE_FORCEINLINE
     eve::common_value_t<T0, T1, T2> operator()(T0 a, T1 b, T2 c) const noexcept
    { return EVE_DISPATCH_CALL(a, b, c); }

    EVE_CALLABLE_OBJECT(ellint_rf_t, ellint_rf_);
  };

  //================================================================================================
  //! @addtogroup elliptic
  //! @{
  //!   @var ellint_rf
  //!   @brief Computes the Carlson's elliptic integral
  //!   \f$  \mathbf{R}_\mathbf{F}(x, y) =
  //!   \frac32 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)]^{-1/2}
  //!   (t+z)^{-3/2}\scriptstyle\;\mathrm{d}t\f$.
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
  //!      constexpr auto ellint_rf(floating_value auto x, floating_value auto y, floating_value auto z)   noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto ellint_rf[conditional_expr auto c](floating_value auto x, floating_value auto y,
  //!                                                        floating_value auto z)                        noexcept; // 2
  //!      constexpr auto ellint_rf[logical_value auto m](floating_value auto x, floating_value auto y,
  //!                                                     floating_value auto z)                           noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`, `z`:  [floating values](@ref eve::floating_value).
  //!                       All those arguments must be non-negative and at most one zero or the
  //!                       the result is NaN.
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. the value of the \f$\mathbf{R}_\mathbf{F}\f$ Carlson elliptic integral:
  //!       \f$  \mathbf{R}_\mathbf{F}(x, y) =
  //!       \frac32 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)]^{-1/2}
  //!       (t+z)^{-3/2}\scriptstyle\;\mathrm{d}t\f$.  is returned
  //!     2. [The operation is performed conditionnaly](@ref conditional)
  //!
  //!  @groupheader{External references}
  //!   *  [DLMF](https://dlmf.nist.gov/19.2)
  //!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/CarlsonEllipticIntegrals.html)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/elliptic/regular/ellint_rf.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto ellint_rf = functor<ellint_rf_t>;

  namespace detail
  {
    template<typename T, callable_options O >
    constexpr auto ellint_rf_(EVE_REQUIRES(cpu_), O const&, T x, T y, T z) noexcept
    {
      if constexpr(O::contains(raw2))
      {
        T    xn   = x;
        T    yn   = y;
        T    zn   = z;
        T    an   = (x + y + z) / 3;
        T    a0   = an;
        auto epsi = pow_abs(3 * eps(as(element_type_t<T>())), -1 / T(8));
        T    q  = epsi * (eve::max)((eve::max)(eve::abs(an - xn), eve::abs(an - yn)), eve::abs(an - zn));
        T    fn = one(as(x));

        // duplication
        unsigned k  = 1;
        T        hf = half(as(x));
        for( ; k < 30; ++k )
        {
          T root_x = eve::sqrt(xn);
          T root_y = eve::sqrt(yn);
          T root_z = eve::sqrt(zn);
          T lambda = root_x * root_y + root_x * root_z + root_y * root_z;
          an       = average(an, lambda) * hf;
          xn       = average(xn, lambda) * hf;
          yn       = average(yn, lambda) * hf;
          zn       = average(zn, lambda) * hf;
          q *= T(0.25);
          fn *= T(4);
          if( eve::all(q < eve::abs(an)) ) break;
        }
        T denom = rec[pedantic2](an * fn);
        T xx    = (a0 - x) * denom;
        T yy    = (a0 - y) * denom;
        T zz    = -xx - yy;

        // Taylor series expansion to the 7th order
        T p  = xx * yy;
        T e2 = fnma(zz, zz, p);
        T e3 = p * zz;
        // TODO put constant values in expansion
        using elt_t        = element_type_t<T>;
        constexpr elt_t c0 = sizeof(elt_t) == 4 ? 1 / 14.0f : 1 / 14.0;
        constexpr elt_t c1 = sizeof(elt_t) == 4 ? 3 / 104.0f : 3 / 104.0;
        constexpr elt_t c2 = sizeof(elt_t) == 4 ? -1 / 10.0f : -1 / 10.0;
        constexpr elt_t c4 = sizeof(elt_t) == 4 ? 1 / 24.0f : 1 / 24.0;
        constexpr elt_t c5 = sizeof(elt_t) == 4 ? -3 / 44.0f : -3 / 44.0;
        constexpr elt_t c6 = sizeof(elt_t) == 4 ? -5 / 208.0f : -5 / 208.0;
        constexpr elt_t c7 = sizeof(elt_t) == 4 ? -1 / 16.0f : 1 / 16.0;
        return (fma(e3,
                    fma(e3, c1, c0),
                    fma(e2, (c2 + e3 * c5 + e2 * (c4 + e2 * c6 + e3 * c7)), one(as(x)))))
          * rsqrt(an);
      }
      else
      {
        auto r = nan(as(x));
        auto notdone =
          is_nltz(x) && is_nltz(y) && is_nltz(z) && is_nez(x + y) && is_nez(y + z) && is_nez(z + x);
        // any parameter nan or less than zero or more than one parameter zero implies nan
        auto br0 = [x, y, z]() { return ellint_rf[raw](x, y, z); };
        last_interval(br0, notdone, r);
        return r;
      }
    }
  }
}
