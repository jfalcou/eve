//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_TAN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_TAN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/detail/scalar/tan_finalize.hpp>
#include <eve/module/core/detail/generic/tancot_kernel.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/fnms.hpp>    
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/reduce_large.hpp>
#include <eve/function/reduce_medium.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/function/trigo_tags.hpp>
#include <type_traits>

namespace eve::detail
{
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto tan_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , T a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if (is_not_less_equal(eve::abs(a0), Pio_4<T>())) return Nan<T>(); 
      return tancot_eval(a0); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::tan scalar ] - type is not an IEEEValue"); 
    }   
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto tan_(EVE_SUPPORTS(cpu_)
                                      , small_type const &       
                                      , T a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using i_t =  as_integer_t<T, signed>; 
      T x = eve::abs(a0);
      if (x < Eps<T>()) return a0;       
      if (is_not_less_equal(x, Pio_2<T>())) return Nan<T>();
      i_t n = x > Pio_4<T>(); 
      if (n)
      {
        auto pio2_1 = Ieee_constant<T, 0X3FC90F80, 0X3FF921FB54400000LL>();
        auto pio2_2 = Ieee_constant<T, 0X37354400, 0X3DD0B4611A600000LL>();
        auto pio2_3 = Ieee_constant<T, 0X2E85A300, 0X3BA3198A2E000000LL>();
        T xr = x-pio2_1;
        xr -= pio2_2;
        xr -= pio2_3;
        T y = tancot_eval(xr);
        return bitwise_xor(bitofsign(a0), -rec(y));
      }
      else
      {
        return tancot_eval(a0);
      }
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::tan scalar ] - type is not an IEEEValue"); 
    }   
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto tan_(EVE_SUPPORTS(cpu_)
                                     , medium_type const &       
                                     , T a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if (is_not_finite(a0)) return Nan<T>(); //Nan or Inf input
      if (is_eqz(a0)) return a0;
      const T x =  abs(a0);
      auto [fn, xr, dxr] = reduce_medium(x); 
      return tan_finalize(a0, fn, xr, dxr); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::tan scalar ] - type is not an IEEEValue"); 
    }   
  }  
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto tan_(EVE_SUPPORTS(cpu_)
                                     , big_type const &       
                                     , T a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if (is_not_finite(a0)) return Nan<T>(); //Nan or Inf input
      if (is_eqz(a0)) return a0;
      const T x =  abs(a0);
      auto [fn, xr, dxr] = reduce_large(x);
      return tan_finalize(a0, fn, xr, dxr);
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::tan scalar ] - type is not an IEEEValue"); 
    }   
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto tan_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  requires(T, vectorizable<T>)
  {
    const T medthresh = Ieee_constant < T, 0x58d776beU,  0x42F0000000000000ULL >(); // 1.89524E+15f
    auto x =  abs(a0);
    if (x <= Pio_4(as(x)))        return restricted_(tan)(a0);
    else if (x <= Pio_2(as(x)))   return small_(tan)(a0);
    else if (x <= medthresh)      return medium_(tan)(a0);
    else                          return big_(tan)(a0);      
  }
  
}

#endif
