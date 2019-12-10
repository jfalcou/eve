//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SINCOS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SINCOS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/module/core/detail/simd/sincos_finalize.hpp>
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
#include <eve/function/combine.hpp>
#include <type_traits>

namespace eve::detail
{

  // limites d'usages  0.5ulp de std::sin
  // restricted abs(x) < pi/4
  // small      abs(x) < pi/2
  // medium     abs(x) <  1.76859e+15 (float) et  281474976710656.0 (double)
  // big        le reste
  
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto sincos_(EVE_SUPPORTS(cpu_)
                           , restricted_type const &     
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    using t_t  = eve::wide<T,N,ABI>;
    auto pi2_16 = Ieee_constant<T, 0X3F1DE9E7U, 0x3FE3BD3CC9BE45DEULL>(); //0.61685027506808491367715568749226 but rounded upward
    auto x2 = sqr(a0);
    x2 = if_else(is_not_less_equal(x2, pi2_16), eve::allbits_, x2);
    return std::tuple<t_t, t_t>{sin_eval(x2, a0), cos_eval(x2)}; 
  }
  
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto internal_sincos( small_type const &       
                                       , eve::wide<T,N,ABI> const &a0) noexcept
  {
    using t_t  = eve::wide<T,N,ABI>;
    auto pio2_1 = Ieee_constant<t_t, 0X3FC90F80, 0X3FF921FB54400000LL>();
    auto pio2_2 = Ieee_constant<t_t, 0X37354400, 0X3DD0B4611A600000LL>();
    auto pio2_3 = Ieee_constant<t_t, 0X2E85A300, 0X3BA3198A2E000000LL>();
    t_t x = eve::abs(a0);
    x = if_else(is_not_less_equal(x, Pio_2<t_t>()), eve::allbits_, x); 
    auto test = is_not_less_equal(x, Pio_4<t_t>()); 
    auto n = binarize(test);
    t_t xr =  x-pio2_1;
    xr -= pio2_2;
    xr -= pio2_3;
    xr = if_else(test, xr, x);
    return  sincos_finalize(a0, n, xr, t_t(0));
  }

template<typename T,  typename N,  typename ABI>
EVE_FORCEINLINE auto internal_sincos(medium_type const &       
                                       , eve::wide<T,N,ABI> const &a0) noexcept
  {
    using t_t  = eve::wide<T,N,ABI>;
    const t_t x = eve::abs(a0);
    auto [n, xr, dxr] = reduce_medium(x);
    return sincos_finalize(a0, n, xr, dxr); 
  }   

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto internal_sincos(big_type const &       
                                       , eve::wide<T,N,ABI> const &a0) noexcept
  {
    using t_t  = eve::wide<T,N,ABI>;
    const t_t x = eve::abs(a0);
    auto [n, xr, dxr] = reduce_large(x); 
    return sincos_finalize(a0, n, xr, dxr); 
  }

  template<typename T,  typename N,  typename ABI, typename TAG>
  EVE_FORCEINLINE auto sincos_(EVE_SUPPORTS(cpu_)
                              , TAG const & tag       
                              , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(is_emulated_v<ABI> ) return map(tag(sincos), a0); 
      else if constexpr(is_aggregated_v<ABI> )
      {
        auto  [lo, hi] = a0.slice();
        auto  [xhi, ehi]   = TAG()(sincos)(hi);
        auto  [xlo, elo]   = TAG()(sincos)(lo);
        return std::tuple<wide<T, N>, wide<T, N>>(eve::combine( xlo, xhi), eve::combine( elo, ehi)); 
      }
      else return internal_sincos(tag, a0);
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::sincos simd ] - type is not an IEEEValue"); 
    }   
  }
  
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto sincos_(EVE_SUPPORTS(cpu_)
                              , eve::wide<T,N,ABI> const &a0) noexcept
  {
    const T medthresh = Ieee_constant < T, 0x58d776beU,  0x42F0000000000000ULL >(); // 1.89524E+15f
    auto x =  abs(a0);
    if (all(x <= Pio_4(as(x))))       return restricted_(sincos)(a0);
    else if(all(x <= Pio_2(as(x))))   return small_(sincos)(a0);
    else if(all(x <= medthresh))      return medium_(sincos)(a0);
    else return big_(sincos)(a0);
  }
}

#endif
