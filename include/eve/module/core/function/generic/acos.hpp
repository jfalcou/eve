//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ACOS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ACOS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/asin.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>    
#include <eve/constant/zero.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE auto acos_(EVE_SUPPORTS(cpu_)
                           ,  raw_type const & 
                            , T const &a0) noexcept
  {
    using t_abi = abi_type_t<T>;
    if constexpr(native<t_abi> || scalar_value<T>)
    {
      auto tmp = Pio_2(as(a0)) +  (Ieee_constant<T, 0XB33BBD2EU, 0x3c91a62633145c07ll>()-asin(a0));
      return if_else(a0 == One(as(a0)), eve::zero_, tmp);
    }
    else
      return apply_over(raw_(acos), a0); 
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto acos_(EVE_SUPPORTS(cpu_)
                            , T const &a0) noexcept
  {
    if constexpr( simd_value<T>)
    {
      if constexpr(native<T>)
      {
        auto x = eve::abs(a0);
        auto x_larger_05 = is_greater(x, eve::Half(as(a0)));
        x  = if_else(x_larger_05, eve::sqrt(fma(eve::Mhalf(as(a0)), x, eve::Half(as(a0)))), a0);
        x  = asin(x);
        x =  add[x_larger_05](x, x);
        x  = eve::if_else(is_less(a0, eve::Mhalf(as(a0))), eve::Pi(as(a0))-x, x);
        return eve::if_else(x_larger_05, x, eve::Pio_2(as(a0))-x);
      }
      else
        return apply_over(acos, a0); 
    }
    else if constexpr( scalar_value<T>)
    {
      if constexpr(std::same_as<T, float>)
      {
        if (a0 < -0.5f)
          return Pi<T>()-eve::asin( sqrt(inc(a0)*Half<T>()))*2.0f;
        else if (a0 > 0.5f)
          return eve::asin( sqrt(oneminus(a0)*Half<T>()))*2.0f;
        return (Pio_2<T>()-eve::asin(a0));
      }
      else if constexpr(std::same_as<T, double>)
      {
        if(a0 == One(as(a0)))          return Zero(as(a0));
        else if (eve::abs(a0) > 1.0)   return Nan<T>();
        else if( a0 > 0.5)             return 2.0*eve::asin(eve::sqrt(fma(-0.5, a0, 0.5))) ;
        T z = Pio_4<T>() - eve::asin(a0);
        z +=  Constant<T,  0X3C81A62633145C07ULL>();//Pio_4lo<T>();
        z += Pio_4<T>();
        return z;
      }
    }
  }
}

#endif
