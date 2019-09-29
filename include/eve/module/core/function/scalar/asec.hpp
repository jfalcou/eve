//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ASEC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ASEC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/acsc.hpp>
#include <eve/function/acos.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto asec_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  requires(T, floating_point<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if (is_equal(a0, One(as(a0)))) return Zero(as(a0));
      return Pio_2(as(a0)) +  (Ieee_constant<T, 0XB33BBD2EU, 0x3c91a62633145c07ll>()-acsc(a0));
    }
     else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::asec scalar ] - type is not an IEEEValue"); 
    }
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto asec_(EVE_SUPPORTS(cpu_)
                                  , pedantic_type const &     
                                  , T const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      return pedantic_(acos)(rec(a0)); 
    }
    return T();
  }

}

#endif
