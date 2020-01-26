//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_CEIL2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_CEIL2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/exp2.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/log2.hpp>
#include <eve/function/ceil.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto ceil2_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      if (is_eqz(v)) return v;
      if (is_less_equal(v, One(as(v)))) return One(as(v)); 
      auto [m, e] = ifrexp(v);
      e = dec[(m == Half<T>())](e); 
      return ldexp(One(as(v)), e); 
    }
    else 
    { 
      if ((v & (v - 1)) == 0)
        return v; 
      else
      {
        T tmp = (v | (v >> 1)) + 1; 
        return ceil2(tmp);
      }
    }
  }
}

#endif
