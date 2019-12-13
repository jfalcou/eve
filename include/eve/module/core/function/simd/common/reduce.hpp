//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REDUCE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REDUCE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/all.hpp>
#include <eve/function/any.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/function/reduce_medium.hpp>
#include <eve/function/reduce_large.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/detail/abi.hpp>
#include <eve/assert.hpp>
#include <type_traits>
#include <tuple>


namespace eve::detail
{
  template < typename T, typename N,  typename ABI>
  EVE_FORCEINLINE auto  reduce_(EVE_SUPPORTS(cpu_)
                                     , wide<T, N, ABI> const &x) noexcept
  requires(std::tuple<wide<T, N, ABI>, wide<T, N, ABI>, wide<T, N, ABI>>, vectorizable<T>)
  {
    EVE_ASSERT(all(is_nltz(x)), "attempted reduce with negative argument"); 
    using t_t = wide < T, N, ABI>; 
    if constexpr(is_emulated_v<ABI>)
    {
      return map(eve::reduce, x);
    }
    else if constexpr(is_aggregated_v<ABI>)
    {
      auto  [lo, hi] = x.slice();
      auto  [nhi, xhi, dxhi] = reduce(hi);
      auto  [nlo, xlo, dxlo] = reduce(lo);
      return std::make_tuple( eve::combine( nlo, nhi)
                                      , eve::combine( xlo, xhi)
                                      , eve::combine( dxlo, dxhi));
    }
    else
    {    
      if (all(x <= Pio_4<T>())) return  std::make_tuple(t_t(0), x, t_t(0)); 
      else
      {
        if constexpr(std::is_same_v<T, float>)
        {                   
          if (all(x <= 120.0f))  return reduce_fast(x); 
          else if (all(x <= 1.89e+15f)) return reduce_medium(x); 
          else return reduce_large(x); 
        }
        else if constexpr(std::is_same_v<T, double>)
        {
          if (all(x <=  105414350.0))  return reduce_fast(x); 
          else if (all(x <=  281474976710656.0)) return reduce_medium(x); 
          else return reduce_large(x); 
        }
      }
    }
  }
}


#endif
 
