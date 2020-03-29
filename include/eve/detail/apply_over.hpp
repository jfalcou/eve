//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_APPLY_OVER_HPP_INCLUDED
#define EVE_DETAIL_APPLY_OVER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/function/combine.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  
  template<typename Obj, simd_value T>
  EVE_FORCEINLINE auto apply_over(Obj f, T const & v)
  {
         if constexpr(has_aggregated_abi_v<T>) return aggregate(f, v);
    else if constexpr(has_emulated_abi_v<T>)   return map(f, v);
  }

  template<typename Obj, value T, value U>
  EVE_FORCEINLINE auto apply_over(Obj f, T const & v, U const & w)
  requires simd_value<T> || simd_value<U>  
  {
         if constexpr(has_aggregated_abi_v<T>) return aggregate(f, v, w);
    else if constexpr(has_emulated_abi_v<T>)   return map(f, v, w);
  }

  template<typename Obj, simd_value T>
  EVE_FORCEINLINE auto apply_over2(Obj f, T const & v)
  {
    if constexpr(has_emulated_abi_v<T> ) return map(f, v); 
    else if constexpr(has_aggregated_abi_v<T>)
    {
      auto  [lov, hiv] = v.slice();
      auto  [xhi, ehi] = f(hiv);
      auto  [xlo, elo] = f(lov);
      return std::make_tuple(eve::combine(xlo, xhi), eve::combine(elo, ehi)); 
    }
  }
  
  template<typename Obj, simd_value T>
  EVE_FORCEINLINE auto apply_over2(Obj f, T const & v, T const & w)
  {
    if constexpr(has_emulated_abi_v<T> ) return map(f, v, w); 
    else if constexpr(has_aggregated_abi_v<T>)
    {
      auto  [lov, hiv] = v.slice();
      auto  [low, hiw] = w.slice();
      auto  [xhi, ehi] = f(hiv, hiw);
      auto  [xlo, elo] = f(lov, low);
      return std::make_tuple(eve::combine(xlo, xhi), eve::combine(elo, ehi)); 
    }
  } 
}

#endif
