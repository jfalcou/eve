//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ASIN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ASIN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrteps.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto asin_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  requires(T, floating<T>)
  {
    T x = eve::abs(a0);
    T sgn = eve::bitofsign(a0);
    if constexpr(std::is_same_v<T, float>)
    {
      const auto x_larger_05 = x > eve::Half<T>();
      T z = if_else(x_larger_05, eve::Half<T>()*eve::oneminus(x), eve::sqr(x));
      x = if_else(x_larger_05, sqrt(z), x);
      // Remez polynomial of degree 4 for (asin(rx)-rx)/(rx*rx*rx) in [0, 0.25]
      // 2120752146 values (99.53%) within 0.0 ULPs
      //    9954286 values (0.47%)  within 0.5 ULPs
      // 4.0 cycles/element SSE4.2 g++-4.8
      T z1 = horn<T,
        0x3e2aaae4,
        0x3d9980f6,
        0x3d3a3ec7,
        0x3cc617e3,
        0x3d2cb352
        > (z);
      z1 = eve::fma(z1, z*x, x);
      z = if_else(x_larger_05, eve::Pio_2<T>()-(z1+z1), z1);
      return eve::bitwise_xor(z, sgn);
    }
    else
    {
      if ((x >  One<T>())) return Nan<T>();
      if ((x <  Sqrteps<T>())) return a0;
      T zz;
      if((x >  Constant<double,0x3fe4000000000000ull> ())) //0.625;
      {
        zz = oneminus(x);
        const T vp = zz*horn<T,
          0x403c896240f3081dll,
          0xc03991aaac01ab68ll,
          0x401bdff5baf33e6all,
          0xbfe2079259f9290fll,
          0x3f684fc3988e9f08ll
          >(zz)/
          horn1<T,
          0x40756709b0b644bell,
          0xc077fe08959063eell,
          0x40626219af6a7f42ll,
          0xc035f2a2b6bf5d8cll
          >(zz);
        zz = sqrt(zz+zz);
        T z = Pio_4<T>()-zz;
        zz = fma(zz, vp,  Constant<T, 0X3C91A62633145C07ULL>());//Pio_2lo<T>());
        z =  z-zz;
        zz = z+Pio_4<T>();
      }
      else
      {
        zz = sqr(x);
        T z = zz*horn<T,
          0xc020656c06ceafd5ll,
          0x40339007da779259ll,
          0xc0304331de27907bll,
          0x4015c74b178a2dd9ll,
          0xbfe34341333e5c16ll,
          0x3f716b9b0bd48ad3ll
          >(zz)/
          horn1<T,
          0xc04898220a3607acll,
          0x4061705684ffbf9dll,
          0xc06265bb6d3576d7ll,
          0x40519fc025fe9054ll,
          0xc02d7b590b5e0eabll
          >(zz);
        zz = fma(x, z, x);
      }
      return bitwise_xor(sgn, zz);
    }
  }
}

#endif
