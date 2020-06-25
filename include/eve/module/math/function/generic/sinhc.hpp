//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/average.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/nbtrue.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sinh.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/one.hpp>
#include <eve/platform.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sinhc_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if (is_eqz(a0)) return One(as(a0));
        if constexpr(eve::platform::supports_infinites) if(is_infinite(a0)) return Zero<T>();
        if constexpr(eve::platform::supports_denormals)
          return eve::abs(a0) < Eps<T>() ? One<T>() : sinh(a0)/a0;
        else
          return sinh(a0)/a0;
      }
      else
      {
        auto sinhc_kernel =  [](auto x2){
          using elt_t = element_type_t<T>;
          if constexpr(std::is_same_v<elt_t, float>)
          {
            return horn<T,
              0x3f800000, // 1.0f
              0x3e2aaacc, // 1.66667160211E-1f
              0x3c087bbe, // 8.33028376239E-3f
              0x39559e2f  // 2.03721912945E-4f
              > (x2);
          }
          else
          {
             return inc( x2*horn<T,
                         0xc115782bdbf6ab05ull, //  -3.51754964808151394800E5
                         0xc0c694b8c71d6182ull, //  -1.15614435765005216044E4,
                         0xc064773a398ff4feull, //  -1.63725857525983828727E2,
                         0xbfe9435fe8bb3cd6ull  //  -7.89474443963537015605E-1
                      > (x2)/
                         horn1<T,
                         0xc1401a20e4f90044ull, //  -2.11052978884890840399E6
                         0x40e1a7ba7ed72245ull, //   3.61578279834431989373E4,
                         0xc0715b6096e96484ull //  -2.77711081420602794433E2,
                          //  0x3ff0000000000000ull  //   1.00000000000000000000E0
                      > (x2));
          }
        };

        T x = abs(a0);
        auto lt1= is_less(x, One<T>());
        std::size_t nb = nbtrue(lt1);
        T z = Zero<T>();
        if( nb > 0)
        {
          z = sinhc_kernel(sqr(x));
          if(nb >=T::static_size) return z;
        }
        auto test1 = is_greater(x, Maxlog<T>()-Log_2<T>());
        T fac = if_else(test1, Half<T>(), One<T>());
        T tmp = exp(x*fac);
        T tmp1 = (Half<T>()*tmp)/x;
        T r =  if_else(test1, tmp1*tmp, average(tmp, -rec(tmp))/x);
        if constexpr(eve::platform::supports_infinites)
          r = if_else(is_equal(x, Inf<T>()), x, r);
        return if_else(lt1, z, r);
      }
    }
    else
    {
      return apply_over(sinhc, a0);
    }
  }
}
