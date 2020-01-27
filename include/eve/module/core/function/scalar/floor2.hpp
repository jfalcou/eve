//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto floor2_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  requires(T, vectorizable<T>)
  {
    if (is_less(v, One(as(v)))) return Zero(as(v)); 
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      auto [m, e] = ifrexp(v);
      e = dec(e); 
      return ldexp(One(as(v)), e); 
    }
    else 
    {
      auto a0 = v;         
      for(int j = 1; j < sizeof(T)*8 ; j*= 2)
      {
        a0 |= bit_shr(a0, j); 
      }
      return a0-bit_shr(a0, 1); 
    }
  }
}

#endif
