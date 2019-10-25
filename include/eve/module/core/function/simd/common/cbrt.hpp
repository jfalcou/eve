//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_CBRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_CBRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/gather.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_ltz.hpp>  
#include <eve/function/is_not_finite.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/module/core/detail/generic/cbrt_kernel.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto cbrt_(EVE_SUPPORTS(cpu_)
                                      , T x) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
   using t_abi = abi_type_t<T>;
   if constexpr(is_emulated_v<t_abi> ) return map(eve::cbrt, x); 
   else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::cbrt, x);
   else
   {    
     constexpr double cbtr2 = 1.2599210498948731648;   /* 2^(1/3) */
     constexpr double sqr_cbtr2 = 1.5874010519681994748;   /* 2^(2/3) */
     constexpr value_type_t<T> factor[5] =
       {
         1.0 / sqr_cbtr2,
         1.0 / cbtr2,
         1.0,
         cbtr2,
         sqr_cbtr2
       };
     
     /* Reduce X.  XM now is an range  [0.5, 1.0].  */
     auto [xm, xe] = raw_(ifrexp)(eve::abs (x));
     T u = cbrt_kernel(xm); 
     u *= gather(&factor[0], 2 + xe-(xe/3)*3);
     u = unary_minus[is_ltz(x)](u); 
     return if_else(is_eqz(x) || is_not_finite(x), x, eve::ldexp(u, xe/3)); 
   }
  }
}

#endif
