//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/module/core/detail/simd/cot_finalize.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/rempio2.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
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
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cot_(EVE_SUPPORTS(cpu_)
                           , restricted_type const &     
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto pi2_16 = Ieee_constant<T, 0X3F1DE9E7U, 0x3FE3BD3CC9BE45DEULL>(); //0.61685027506808491367715568749226 but rounded upward
      return if_else(is_not_less_equal(sqr(a0), pi2_16), eve::allbits_, rec(tancot_eval(a0))); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cot simd ] - type is not an IEEEValue"); 
      return T(); 
    }   
  }

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cot_(EVE_SUPPORTS(cpu_)
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
      auto test = is_not_less_equal(x, Pio_4<t_t>()); 
      t_t xr =  x-pio2_1;
      xr -= pio2_2;
      xr -= pio2_3;
      xr = if_else(test, xr, x);
      auto y = tancot_eval(xr); 
      y = if_else(is_not_finite(a0), eve::allbits_, if_else(test, -y, rec(y))); 
      return if_else(abs(a0) <= Eps<t_t>(), rec(a0), bit_xor(bitofsign(a0), y)); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cot simd ] - type is not an IEEEValue"); 
      return T(); 
    }   
  }
 
  template<typename D, typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cot_(EVE_SUPPORTS(cpu_)
                           , D const &       
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using t_t  = eve::wide<T,N,ABI>;
      const t_t x = eve::abs(a0);
      auto [n, xr, dxr] = D()(rempio2)(x);
      return cot_finalize(a0, n, xr, dxr); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cot simd ] - type is not an IEEEValue");
      return T(); 
    }   
  }   

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cot_(EVE_SUPPORTS(cpu_)
                            , eve::wide<T,N,ABI> const &a0) noexcept
  {
    auto x =  eve::abs(a0);
    if (all(x <= Pio_4(as(x))))                                   return restricted_(cot)(a0);
    else if(all(x <= Pio_2(as(x))))                               return small_(cot)(a0);
    else if(all(x <= Rempio2_limit(eve::medium_type(), T())))     return medium_(cot)(a0);
    else                                                          return big_(cot)(a0);
  }
}

#endif
