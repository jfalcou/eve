//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/module/core/detail/simd/cos_finalize.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/function/reduce_medium.hpp>
#include <eve/function/reduce_large.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/all.hpp>
#include <type_traits>

namespace eve::detail
{

  // limites d'usages  0.5ulp de std::sin
  // restricted abs(x) < pi/4
  // small      abs(x) < pi/2
  // medium     abs(x) <  1.76859e+15 (float) et  281474976710656.0 (double)
  // big        le reste
  
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cos_(EVE_SUPPORTS(cpu_)
                           , restricted_type const &     
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto pi2_16 = Ieee_constant<T, 0X3F1DE9E7U, 0x3FE3BD3CC9BE45DEULL>(); //0.61685027506808491367715568749226 but rounded upward
      auto x2 = sqr(a0); 
      return if_else(is_not_less_equal(x2, pi2_16), eve::allbits_, cos_eval(x2)); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos simd ] - type is not an IEEEValue"); 
    }   
  }

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cos_(EVE_SUPPORTS(cpu_)
                           , small_type const &       
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using t_t  = eve::wide<T,N,ABI>;
      auto pio2_1 = Ieee_constant<t_t, 0X3FC90F80, 0X3FF921FB54400000LL>();
      auto pio2_2 = Ieee_constant<t_t, 0X37354400, 0X3DD0B4611A600000LL>();
      auto pio2_3 = Ieee_constant<t_t, 0X2E85A300, 0X3BA3198A2E000000LL>();
      t_t x = eve::abs(a0);
      t_t n = binarize(is_not_less_equal(x, Pio_4<t_t>())); 
      t_t xr =  x-pio2_1;
      xr -= pio2_2;
      xr -= pio2_3;
      xr = if_else(n, xr, x); 
      auto sign_bit = binarize(is_nez(n), Signmask<T>());
      const t_t z = sqr(xr);
      const t_t se = bitwise_xor(detail::sin_eval(z, xr), sign_bit);
      const t_t ce = detail::cos_eval(z);
      const t_t z1 = if_else(n, se, ce);
      return if_else(is_not_less_equal(x, Pio_2<t_t>()), Nan<t_t>(), z1); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos simd ] - type is not an IEEEValue"); 
    }   
  }

  template<typename N,  typename ABI>
  EVE_FORCEINLINE auto cos_upgrade( eve::wide<float,N,ABI> const & a0) noexcept
  {
//    using dt_t = eve::wide<double,N,ABI>;
    auto x =  eve::abs(convert(a0, double_)); 
    static const double
      pio2_1  = -1.57079631090164184570e+00, /* 0x3FF921FB, 0x50000000 */
      pio2_1t = -1.58932547735281966916e-08; /* 0x3E5110b4, 0x611A6263 */
    auto fn = nearest(x*Twoopi<double>());
    auto xr = fma(fn, pio2_1t, fma(fn, pio2_1, x));
    auto fxr = convert(xr, single_); 
    return detail::cos_finalize( convert(fn, single_), fxr, convert(xr-convert(fxr, double_), single_)); 
  }
  
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cos_(EVE_SUPPORTS(cpu_)
                           , medium_type const &       
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using t_t  = eve::wide<T,N,ABI>;
      const t_t x = eve::abs(a0);
      auto [n, xr, dxr] = reduce_medium(x);
      return detail::cos_finalize(n, xr, dxr); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos simd ] - type is not an IEEEValue"); 
    }   
  }   
  
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cos_(EVE_SUPPORTS(cpu_)
                           , big_type const &       
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using t_t  = eve::wide<T,N,ABI>;
      const t_t x = eve::abs(a0);
      auto [n, xr, dxr] = reduce_large(x); 
      return detail::cos_finalize(n, xr, dxr); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos simd ] - type is not an IEEEValue"); 
    }   
  }


  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cos_(EVE_SUPPORTS(cpu_)
                            , eve::wide<T,N,ABI> const &a0) noexcept
  {
    const T medthresh = Ieee_constant < T, 0x58d776beU,  0x42F0000000000000ULL >(); // 1.89524E+15f
    auto x =  abs(a0);
    if (all(x <= Pio_4(as(x))))       return restricted_(cos)(a0);
    else if(all(x <= Pio_2(as(x))))   return small_(cos)(a0);
    else if(all(x <= medthresh))      return medium_(cos)(a0);
    else return big_(cos)(x);
  }
}

#endif
