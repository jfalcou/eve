//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/function/combine.hpp>

namespace eve::detail
{

  // -----------------------------------------------------------------------------------------------
  // N parameters apply_over
  template<typename Obj, value T0, value ... T>
  EVE_FORCEINLINE  auto apply_over(Obj f
                                  , T0 const & arg0
                                  , T const &... args ) noexcept
  requires simd_value<T0> || (simd_value<T> ||  ...)
  {
    constexpr bool any_aggregated = has_aggregated_abi_v<T0> || (has_aggregated_abi_v<T> || ...);
    constexpr bool any_emulated   = has_emulated_abi_v<T0>   || (has_emulated_abi_v<T>   || ...);
         if constexpr(any_aggregated) return aggregate(f, arg0, args...);
    else if constexpr(any_emulated)   return map(f, arg0, args...);
    else                              return f(arg0, args...);

  }

  template<typename Obj, simd_value T>
  EVE_FORCEINLINE auto apply_over(Obj f, T const & v)
  {
         if constexpr(has_aggregated_abi_v<T>) return aggregate(f, v);
    else if constexpr(has_emulated_abi_v<T>)   return map(f, v);
    else                                       return f(v);
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
      return kumi::make_tuple(eve::combine(xlo, xhi), eve::combine(elo, ehi));
    }
    else return f(v);
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
      return kumi::make_tuple(eve::combine(xlo, xhi), eve::combine(elo, ehi));
    }
    else return f(v, w);
  }

  template<typename Obj, simd_value T>
  EVE_FORCEINLINE auto apply_over3(Obj f, T const & v)
  {
    if constexpr(has_emulated_abi_v<T> ) return map(f, v);
    else if constexpr(has_aggregated_abi_v<T>)
    {
      auto  [lo, hi] = v.slice();
      auto  [nhi, xhi, dxhi] = f(hi);
      auto  [nlo, xlo, dxlo] = f(lo);
      return kumi::make_tuple ( eve::combine( nlo, nhi)
                              , eve::combine( xlo, xhi)
                              , eve::combine( dxlo, dxhi)
                              );
    }
    else return f(v);
  }
}
