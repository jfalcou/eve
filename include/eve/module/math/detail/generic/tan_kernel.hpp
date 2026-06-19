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
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/constant/pi2o_16.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/constant/pi.hpp>

#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>
#include <eve/module/math/regular/div_180.hpp>
#include <eve/module/math/detail/generic/rem180.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>
#include <eve/module/math/regular/deginrad.hpp>

namespace eve
{
  namespace _::ab_st //Abramowitz & Stegun
  {

     template <typename T> inline T pade_tan12(T a0) // good for raw tan(a0) -pi/4 < a0 <  pi/4 (3.0e-3)
    {
      using elt_t =  element_type_t<T>;
      constexpr elt_t a = 24.35227277;
      constexpr elt_t b = 9.869604404;
      constexpr elt_t c = 0.710131865;
      constexpr elt_t d = 2.467401100272339;  //pi^2/4
      auto a02 = sqr(a0); ;
      return a*a0/fam(b, c, a02)/(d-a02);
   }

    template <typename T> inline T pade_tan32(T a0) // good for raw tan(a0) -pi/2 < a0 <  pi/2  (4e-2)
    {                                               // or fast tan(a0)      -pi/4 < a0 <  pi/4  (7.0e-6)
      using elt_t =  element_type_t<T>;
      constexpr elt_t a =315.3924266860481;   // 15*pi2*(12-pi2)
      constexpr elt_t b = -30.41464490063611; //720+60*pi2+pi2*pi2
      constexpr elt_t c = -383.4712078039155; //-180(12-pi2)
      constexpr elt_t d = 9.388483121566225;  //72*(10-pi2)
      constexpr elt_t e = 2.467401100272339;  //pi^2/4
      auto a02 = sqr(a0); ;
      return 3*a0 * fam(a, b, a02)/((a02- e)*fam(c, d, a02));
   }

     template <typename T> inline T pade_tan52(T a0) // good for fast  tan(a0) -pi/2 < a0 <  pi/2 (1.0e-4)
    {
      using elt_t =  element_type_t<T>;
      auto a02 = sqr(a0);
      constexpr elt_t a = -0.00035748693;
      constexpr elt_t b = 0.00003986845;
      constexpr elt_t c = -3.881386e-7;
      constexpr elt_t d = -0.130395596;
      constexpr elt_t e =  0.005160122;
      constexpr elt_t f = 2.467401100272339;  //pi^2/4

      return -900*a0*fam(a, a02, fam(b, c, a02))/(fam(d, e, a02)*(a02- f));
   }

   template <typename T> inline T fast_tan(T a0) // tan(a0) -pi/2 < a0 <  pi/2
    {
      using elt_t =  element_type_t<T>;
      constexpr elt_t c0 = 2.4674011002723397;
      constexpr elt_t c1 = 2.471688400562703;
      constexpr elt_t c2 = 0.189759681063053;
      auto a02 = sqr(a0); ;
      return a0 * fam(c1, -c2,  a02) / (c0 - a02);
   }

    template <typename T> inline T raw_tan(T a0)// tan(a0) -pi/2 < a0 <  pi/2
    {
      using elt_t =  element_type_t<T>;
      a0*= 2*inv_pi(as<elt_t>());
      auto y = oneminus(sqr(a0));
      constexpr elt_t c0(-0.0187108);
      constexpr elt_t c1(0.31583526);
      constexpr elt_t c2(1.27365776);
      return a0*horner(a0, c0, c1, c2)/y; //absolute error less than Z.0e-3
    }

    template <typename T> inline T fast_tanc(T a0) // tan(a0)/a0 -pi/4 < a0 <  pi/4
    {
      using elt_t =  element_type_t<T>;
      constexpr elt_t c0(1);
      constexpr elt_t c2(0.3333314036);
      constexpr elt_t c4(0.1333923995);
      constexpr elt_t c6(0.0533740603);
      constexpr elt_t c8(0.0245650893);
      constexpr elt_t c10(0.0029005250);
      constexpr elt_t c12(0.0095168091);
      return reverse_horner(sqr(a0), c0, c2, c4, c6, c8, c10, c12); //absolute error less than 2.0e-8
    }

    template <typename T> inline T raw_tanc(T a0)// cos(a0) -pi/4 < a0 <  pi/4
    {
      using elt_t =  element_type_t<T>;
      constexpr elt_t c0(1);
      constexpr elt_t c2(0.31755);
      constexpr elt_t c4(0.20330);
      return reverse_horner(sqr(a0), c0, c2, c4); //absolute error less than 1.0e-3
    }
  }

  template<typename Options>
  struct tan_kernel_t : elementwise_callable<tan_kernel_t, Options, quarter_circle_option,
                                             half_circle_option, full_circle_option,
                                             medium_option, big_option,
                                             rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(tan_kernel_t, tan_kernel_);
  };

  inline constexpr auto tan_kernel = functor<tan_kernel_t>;

}

namespace eve::_
{
  template<floating_value T, callable_options O> EVE_NOINLINE
  T tan_kernel_(EVE_REQUIRES(cpu_), O const& o, T a0) noexcept
  {
    if constexpr(O::contains(deg))
    {
      if constexpr(O::contains(quarter_circle))
      {
        return tan_kernel[radpi][eve::quarter_circle](div_180(a0));
      }
      else
      {
        auto x = eve::abs(a0);
        if( eve::all(x <= T(45)) ) return tan_kernel[deg][eve::quarter_circle](a0);
        auto a0_180 = div_180(a0);
        auto test   = is_not_flint(a0_180) && is_flint(a0_180 + mhalf(eve::as(a0_180)));
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return a0;
          if( test ) return nan(eve::as<T>());
        }
        else
          x = if_else(test, eve::allbits, x);
        auto [fn, xr, dxr] = rem180(x);
        return tan_finalize(deginrad(a0), fn, xr, dxr);
      }
    }
    else if constexpr(O::contains(radpi))
    {
      if constexpr(O::contains(quarter_circle))
      {
        return tan_kernel[eve::quarter_circle](a0 * pi(eve::as<T>()));
      }
      else
      {
        auto x = eve::abs(a0);
        if( eve::all(x <= T(0.25)) ) return tan_kernel[radpi][eve::quarter_circle](a0);
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return a0;
          if( is_not_finite(x) || (frac[raw](x) == half(eve::as<T>())) ) return nan(eve::as<T>());
          if( x > maxflint(eve::as<T>()) || is_flint(x) ) return T(0);
        }
        else
        {
          x = if_else(is_greater(x, maxflint(eve::as(x))) || is_flint(x), eve::zero, x);
          x = if_else(is_not_finite(a0) || (frac[raw](x) == half(eve::as<T>())), eve::allbits, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return tan_finalize(a0 * pi(eve::as<T>()), fn, xr, dxr);
      }
    }
    else
    {
      if constexpr(O::contains(quarter_circle))
      {
        if constexpr( scalar_value<T> )
        {
          if( is_not_less_equal(eve::abs(a0), pio_4(eve::as<T>())) ) return nan(eve::as<T>());
        }
        else
        {
          auto pi2_16 =  pi2o_16[upper](as<T>());
          a0 = if_else(is_not_less_equal(eve::sqr(a0), pi2_16), eve::allbits, a0);
        }
        return tancot_eval(a0);
      }
      else if constexpr(O::contains(half_circle))
      {
        auto reduce = [](auto xx)
          {
            auto pio2_1 = ieee_constant<0x1.921fb54400000p+0 , 0x1.921f000p+0f >(eve::as<T>{});
            auto pio2_2 = ieee_constant<0x1.0b4611a600000p-34, 0x1.6a88000p-17f>(eve::as<T>{});
            auto pio2_3 = ieee_constant<0x1.3198a2e000000p-69, 0x1.0b46000p-34f>(eve::as<T>{});
            T    xr     = xx - pio2_1;
            xr -= pio2_2;
            xr -= pio2_3;
            return xr;
          };
        T x = eve::abs(a0);
        if constexpr( scalar_value<T> )
        {
          if( x < eps(as<T>()) ) return a0;
          if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return nan(eve::as<T>());
          int n = x > pio_4(eve::as<T>());
          if( n )
          {
            T xr = reduce(x);
            T y  = tancot_eval(xr);
            return bit_xor(bitofsign(a0), -rec[pedantic](y));
          }
          else { return tancot_eval(a0); }
        }
        else if constexpr( simd_value<T> )
        {
          auto test = is_not_less_equal(x, pio_4(eve::as(a0)));
          T    xr   = if_else(test, reduce(x), x);
          auto y    = tancot_eval(xr);
          y         = if_else(is_not_finite(a0), eve::allbits, if_else(test, -rec[pedantic](y), y));
          return if_else(x <= eps(as<T>()), a0, bit_xor(bitofsign(a0), y));
        }
      }
      else if constexpr(O::contains(full_circle) || O::contains(medium) || O::contains(big) )
      {
        auto x       = abs(a0);
        auto xnlelim = is_not_less_equal(x, Rempio2_limit[o](as(a0)));
        if constexpr( scalar_value<T> )
        {
          if( xnlelim ) return nan(eve::as<T>());
          if( is_eqz(a0) ) return a0;
        }
        else x = if_else(xnlelim, allbits, x);
        auto [fn, xr, dxr] = rempio2[o](x);
        return tan_finalize(a0, fn, xr, dxr);
      }
      else
      {
        auto x = abs(a0);
        if( eve::all(x <= Rempio2_limit[quarter_circle](as(a0))) )
          return tan_kernel[quarter_circle](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle](as(a0))))
          return tan_kernel[half_circle](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle](as(a0))))
          return tan_kernel[full_circle](a0);
        else if( eve::all(x <= Rempio2_limit[medium](as(a0))))
          return tan_kernel[medium](a0);
        else
          return tan_kernel[big](a0);
      }
    }
  }
}
