//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_FLOOR2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_FLOOR2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/exp2.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/log2.hpp>
#include <eve/function/ceil.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/meta.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto floor2_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  requires(T, floating_point<T>)
  {
    if (is_less(v, One(as(v)))) return Zero(as(v)); 
    auto [m, e] = ifrexp(v);
    e = dec(e); 
    return ldexp(One(as(v)), e); 
  }


  template<typename T>
  EVE_FORCEINLINE constexpr auto floor2_(EVE_SUPPORTS(cpu_), T v) noexcept
  requires(T, unsigned_type<T>)
  {
    if (v == 0) return v;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    if constexpr( sizeof(T) >= 2 )  v |= v >>  8;
    if constexpr( sizeof(T) >= 4 )  v |= v >> 16;
    if constexpr( sizeof(T) >= 8 )  v |= v >> 32;
    return v-(v>> 1); 
  }  
}

#endif
