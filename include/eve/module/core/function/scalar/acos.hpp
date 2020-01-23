//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ACOS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ACOS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/asin.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/constant.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/raw.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto acos_(EVE_SUPPORTS(cpu_)
                                  , raw_type const &     
                                  , T const &a0) noexcept
  requires(T, floating_point<T>)
  {
    if(a0 == One(as(a0))) return Zero(as(a0));
    return Pio_2(as(a0)) +  (Ieee_constant<T, 0XB33BBD2EU, 0x3c91a62633145c07ll>()-asin(a0));
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto acos_(EVE_SUPPORTS(cpu_)
                                      , T const &a0) noexcept
  requires(T, floating_point<T>)
  {
    if constexpr(std::is_same_v<T, float>)
    {
      if (a0 < -0.5f)
        return Pi<T>()-eve::asin( sqrt(inc(a0)*Half<T>()))*2.0f;
      else if (a0 > 0.5f)
        return eve::asin( sqrt(oneminus(a0)*Half<T>()))*2.0f;
      return (Pio_2<T>()-eve::asin(a0));
    }
    else if constexpr(std::is_same_v<T, double>)
    {
      if(a0 == One(as(a0)))
        return Zero(as(a0));
      else if (eve::abs(a0) > 1.0)
        return Nan<T>();
      else if( a0 > 0.5)
      {
        return 2.0 * eve::asin(  sqrt(fma(-0.5, a0, 0.5) )) ;
      }
      T z = Pio_4<T>() - eve::asin(a0);
      z = z +  Constant<T,  0X3C81A62633145C07ULL>();//Pio_4lo<T>();
      z = z + Pio_4<T>();
      return z;
    }
  }
}

#endif
