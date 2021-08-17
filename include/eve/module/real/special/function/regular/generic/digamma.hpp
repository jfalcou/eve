//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/add.hpp>
#include <eve/function/any.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/epsilon.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/log.hpp>
#include <eve/function/max.hpp>
#include <eve/function/maximum.hpp>
#include <eve/function/min.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE T digamma_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr( has_native_abi_v<T> )
    {
      auto dlarge = (std::is_same_v<elt_t, double>) ? 20: 10;
      auto br_1_2 = [](auto x, auto )
        {
          // computes digamma(a0)/a0 for double or double vectors
          // xx is sqr(a0) and 0 <= abs(a0) <= 3.25
          T y(0.99558162689208984);
          T root1(1569415565.0 / 1073741824uL);
          T root2((381566830.0 / 1073741824uL) / 1073741824uL);
          T root3(0.9016312093258695918615325266959189453125e-19);

          auto g = x - root1;
          g -= root2;
          g -= root3;
          x = dec(x);
          if constexpr(std::is_same_v<elt_t, double>)
          {
            auto r = horn<T,
              0x3fd04e9e69894978ll,
              0xbfd4d5d0f9ab412fll,
              0xbfe4cf68d26e295all,
              0xbfd2821c13c5e2bfll,
              0xbfa72b2e63723c78ll,
              0xbf60f7e5f66c2537ll
              >(x)
              /
              horn<T,
              0x3ff0000000000000ll,
              0x40009d1b06674d41ll,
              0x3ff75eb79397c930ll,
              0x3fdbe65d28de361cll,
              0x3fabb9c8cc612ca3ll,
              0x3f616fc90a0a1908ll,
              0xbea2b84f95bbf448ll
              >(x);
            return fma(g, y, g * r);
          }
          else
          {
            auto r = horn<T,
            0x3e8274f3,
            0xbea6ae88,
            0xbf267b47,
            0xbe9410e1,
            0xbd395973,
            0xbb07bf30
            >(x)
            /
            horn<T,
            0x3f800000,
            0x4004e8d8,
            0x3fbaf5bd,
            0x3edf32e9,
            0x3d5dce46,
            0x3b0b7e48,
            0xb515c27d
            >(x);
            return fma(g, y, g * r);
          }
        };

      auto br_large = [](auto x, auto )
        {
          //if we're above the lower-limit for the asymptotic expansion then use it:
          x = dec(x);
          auto result = log(x);
          result += rec(x+x);
          auto z = rec(sqr(x));
          T y(0);
          if constexpr(std::is_same_v < elt_t, double>)
          {
            y = horn<T, 0x3fb5555555555555ll,  0xbf81111111111111ll,  0x3f70410410410410ll, 0xbf71111111111111ll
              , 0x3f7f07c1f07c1f08ll,0xbf95995995995996ll,0x3fb5555555555555ll,0xbfdc5e5e5e5e5e5ell> (z);
          }
          else
          {
            y = horn<T,0x3daaaaab, 0xbc088889,0x3b820821, 0xbb888889,
            0x3bf83e10,0xbcaccacd,0x3daaaaab,0xbee2f2f3>(z);
          }
          result -= z * y;
          return result;
        };
      if constexpr(scalar_value<T>)
      {
        auto result = zero(as(x));
        if (x == 0) return copysign(inf(as(x)), x);
        if( x < 0)
        {
          if ( 0 && (x > -1))
            result = -x;
          else
          {
            x =  oneminus(x);
            result = x - floor(x);
          }
          if (result > 0.5)  result -= 1;
          if (result == 0.5) result = zero(as(x));
          else if (result) result =pi(as(x))*cotpi(result);
          else  result = nan(as(x));
          // we are ready to increment result that was
          // Pi<A0>()/tanpi(remainder) if a0 < 0  and remainder != 0
          // Nan<A0>                   if a0 < 0  and remainder == 0
          // 0                         in any other cases
        }
        if(x >= dlarge)
        { // If we're above the lower-limit for the asymptotic expansion then use it:
          return br_large(x, result)+result;
        }
        // If x > 2 reduce to the interval [1,2]:
        while(x > 2)
        {
          x      -= 1;
          result += 1/x;
        }
        // If x < 1 use shift to > 1:
        if(x < 1)
        {
          result = -1/x;
          x      += 1;
        }
        return br_1_2(x, result)+result;
      }
      else // simd
      {
        x = if_else(is_ltz(x) && is_flint(x), allbits, x);
        auto notdone = is_not_nan(x);
        auto result = zero(as(x));
        auto test = is_lez(x);
        if( eve::any(test) )
        {
          auto a = x;
          x = oneminus[test](x);
          auto remainder = frac(x);
          remainder = dec[remainder > 0.5](remainder);
          remainder = if_else(is_eqz(remainder), nan(as(x)), remainder);
          remainder = if_else(remainder == T(0.5), zero, pi(as(x))*cotpi(remainder));
          result = if_else(is_eqz(a), copysign(inf(as(x)), a), remainder);
          result = if_else(test, result, zero);
        }
        auto r = nan(as<T>()); //nan case treated here
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_large,  notdone, x > dlarge, r, x, result);
          if( eve::any(notdone) )
          {
            // If x > 2 reduce to the interval [1,2]:
            x = if_else(x > dlarge, one, x);
            auto cond = x > 2;
            while( eve::any(cond) )
            {
              x =  dec[cond](x);
              result = add[cond](result,rec(x));
              cond = x > 2;
            }
            cond = x < 1;
            if( eve::any(cond) ) // back one step
            {
              result = add[cond](-rec(x), result);
              x =  inc[cond](x);
            }
            notdone = last_interval(br_1_2,  notdone, r, x, result);
          }
        }
        return r+result;
      }
    }
    else
      return apply_over(digamma, x);
  }
}
