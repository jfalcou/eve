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
  struct ellint_rd_t : elementwise_callable<ellint_rd_t, Options, raw_option>
  {
    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1, eve::floating_ordered_value T2>
    requires (same_lanes_or_scalar<T0, T1, T2>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1, T2> operator()(T0 a, T1 b, T2 c) const noexcept
   { return EVE_DISPATCH_CALL(a, b, c); }

    EVE_CALLABLE_OBJECT(ellint_rd_t, ellint_rd_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_rd
//!   @brief Computes the Carlson's elliptic integral
//!
//!   \f$  \mathbf{R}_\mathbf{D}(x, y) = \frac32 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)]^{-1/2}
//!   (t+z)^{-3/2}\scriptstyle\;\mathrm{d}t\f$.
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
//!      template< eve::floating_ordered_value T
//!              , eve::floating_ordered_value U
//!              , eve::floating_ordered_value V >
//!      constexpr eve::common_value_t<T, U, V> ellint_rd(T x, U y, V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [floating real arguments](@ref eve::floating_ordered_value). `x` and `y` must be
//!       strictly positive and `y` non zero. In any other case, the result is NaN.
//!     * `z`: strictly positive [floating real arguments](@ref eve::floating_ordered_value). In any other
//!       case, the result is NaN.
//!
//!   **Return value**
//!
//!   the value of the \f$\mathbf{R}_\mathbf{D}\f$ Carlson elliptic integral is returned:
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/elliptic/regular/ellint_rc.cpp}
//! @}
//================================================================================================
inline constexpr auto ellint_rd = functor<ellint_rd_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr auto  ellint_rd_(EVE_REQUIRES(cpu_), O const&, T x, T y, T z) noexcept
    {
      if constexpr(O::contains(raw2))
      {
        using elt_t = element_type_t<T>;
        T    xn     = x;
        T    yn     = y;
        T    zn     = z;
        T    an     = (x + y + T(3) * z) / 5;
        T    a0     = an;
        auto epsi   = pow_abs(elt_t(0.25) * eps(as(element_type_t<T>())), -1 / T(8));
        T    q = epsi * (eve::max)((eve::max)(eve::abs(an - xn), eve::abs(an - yn)), eve::abs(an - zn))
          * elt_t(1.2);
        T fn(one(as(x)));
        T rd_sum(zero(as(x)));

        // duplication
        unsigned k  = 0;
        T        hf = half(as(x));
        for( ; k < 30; ++k )
        {
          T root_x = eve::sqrt(xn);
          T root_y = eve::sqrt(yn);
          T root_z = eve::sqrt(zn);
          T lambda = root_x * root_y + root_x * root_z + root_y * root_z;
          rd_sum += fn / (root_z * (zn + lambda));
          an = average(an, lambda) * hf;
          xn = average(xn, lambda) * hf;
          yn = average(yn, lambda) * hf;
          zn = average(zn, lambda) * hf;
          q *= T(0.25);
          fn *= T(0.25);
          if( eve::all(q < eve::abs(an)) ) break;
        }

        T invan = rec[pedantic2](an);
        T xx    = fn * (a0 - x) * invan;
        T yy    = fn * (a0 - y) * invan;
        T zz    = -(xx + yy) / 3;
        T xxyy  = xx * yy;
        T zz2   = sqr(zz);
        T e2    = fnma(T(6), zz2, xxyy);
        T e3    = (3 * xxyy - 8 * zz2) * zz;
        T e4    = 3 * (xxyy - zz2) * zz2;
        T e5    = xxyy * zz2 * zz;

        constexpr elt_t c0  = sizeof(elt_t) == 4 ? -3 / 14.0f : -3 / 14.0;
        constexpr elt_t c1  = sizeof(elt_t) == 4 ? 1 / 6.0f : 1 / 6.0;
        constexpr elt_t c2  = sizeof(elt_t) == 4 ? 9 / 88.0f : 9 / 88.0;
        constexpr elt_t c3  = sizeof(elt_t) == 4 ? -3 / 22.0f : -3 / 22.0;
        constexpr elt_t c4  = sizeof(elt_t) == 4 ? -9 / 52.0f : -9 / 52.0;
        constexpr elt_t c5  = sizeof(elt_t) == 4 ? 3 / 26.0f : 3 / 26.0;
        constexpr elt_t c6  = sizeof(elt_t) == 4 ? -1 / 16.0f : 1 / 16.0;
        constexpr elt_t c7  = sizeof(elt_t) == 4 ? 3 / 40.0f : 3 / 40.0;
        constexpr elt_t c8  = sizeof(elt_t) == 4 ? 3 / 20.0f : 3 / 20.0;
        constexpr elt_t c9  = sizeof(elt_t) == 4 ? 45 / 272.0f : 45 / 272.0;
        constexpr elt_t c10 = sizeof(elt_t) == 4 ? -9 / 68.0f : -9 / 68.0;

        T e22    = sqr(e2);
        T result = fn * invan * sqrt(invan)
          * (1 + e2 * c0 + e3 * c1 + e22 * c2 + e4 * c3 + e2 * (e3 * c4 + e22 * c6) + e5 * c5
             + sqr(e3) * c7 + e2 * e4 * c8 + c9 * e22 * e3 + (e3 * e4 + e2 * e5) * c10);

        return fma(T(3), rd_sum, result);
      }
      else
      {
        auto r       = nan(as(x));
        auto notdone = is_nltz(x) && is_nltz(y) && is_nlez(z) && is_nez(x + y);
        // z equal to zero or any parameter nan or less than zero or more than one of x and y zero implies
        // nan
        auto br0 = [x, y, z]() { return ellint_rd[raw](x, y, z); }; // o+raw
        last_interval(br0, notdone, r);
        return r;
      }
    }
  }
}
