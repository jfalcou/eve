//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SIN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SIN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/detail/scalar/sin_finalize.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp> 
#include <eve/function/abs.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/fnms.hpp>    
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/rempio2.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/eps.hpp>
#include <eve/function/trigo_tags.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto sin_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , T a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto pi2_16 = Ieee_constant<T, 0X3F1DE9E7U, 0x3FE3BD3CC9BE45DEULL>(); //0.61685027506808491367715568749226 but rounded upward
      auto x2 = sqr(a0);
      auto x  = eve::abs(a0); 
      if (is_not_less_equal(x2, pi2_16)) return Nan<T>(); 
      return bit_xor(detail::sin_eval(x2, x), bitofsign(a0));
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::sin scalar ] - type is not an IEEEValue"); 
      return T(); 
    }   
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto sin_(EVE_SUPPORTS(cpu_)
                                      , small_type const &       
                                      , T a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using i_t = as_integer_t<T, signed>; 
      T x = eve::abs(a0);
      if (is_less_equal(x, Eps<T>())) return a0; 
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

        return  bit_xor(bitofsign(a0), cos_eval(sqr(xr)));
      }
      else
      {
        return sin_eval(sqr(x), a0); 
      }
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::sin scalar ] - type is not an IEEEValue"); 
      return T(); 
    }   
  }

  ////////////////////////////////////////////////////////////////////////
  /// big medium
  template<typename D, typename T>
  EVE_FORCEINLINE constexpr auto sin_(EVE_SUPPORTS(cpu_)
                                     , D const &       
                                     , T a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if (is_not_finite(a0)) return Nan<T>(); //Nan or Inf input
      const T x =  abs(a0);
      auto [fn, xr, dxr] = D()(rempio2)(x);
      return detail::sin_finalize(bitofsign(a0), fn,  xr, dxr); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::sin scalar ] - type is not an IEEEValue");
      return T(); 
    }   
  }  
 
  template<typename T>
  EVE_FORCEINLINE constexpr auto sin_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  requires(T, vectorizable<T>)
  {
    auto x =  abs(a0);
    if (x <= Pio_4(as(x)))                             return restricted_(sin)(a0);
    else if (x <= Pio_2(as(x)))                        return small_(sin)(a0);
    else if ( x <= Rempio2_limit(medium_type(), T()))  return medium_(sin)(a0);
    else                                               return big_(sin)(a0);      
  }
  
}

#endif
