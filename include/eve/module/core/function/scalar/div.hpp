//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>
#include <eve/function/bitwise_mask.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/zero.hpp>
#include <eve/tags.hpp>

namespace eve::detail
{
#ifdef BOOST_MSVC
#pragma warning(push) 
#pragma warning(disable: 4723) // potential divide by 0
#endif

  template<typename T>
  EVE_FORCEINLINE constexpr auto div_(EVE_SUPPORTS(cpu_)
                                     , T const &a
                                     , T const &b) noexcept
  requires(T, Vectorizable<T>)
  {
    return a/b;
  }

  //-----------------------------------------------------------------------------------------------
  // saturated
  template<typename T>
  EVE_FORCEINLINE constexpr auto div_(EVE_SUPPORTS(cpu_)
                                     , saturated_type const &  
                                     , T const &a0
                                     , T const &a1) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>) return a0/a1;
    else if constexpr(std::is_signed_v<T>)
    {
      using ui_t = as_integer_t<T, unsigned>;
      T aa0 = a0 + !((a1 + One(as(a0))) | ((ui_t)a0 + Valmin(as(a0))));
      if (a1)  return aa0/a1;
      else if (a0) return Valmax(as(a0)) + ((ui_t)a0 >> (sizeof(T)*8-1));
      else return Zero(as(a0));
    }
    else /*if constexpr(!std::is_signed_v<T>)*/ return a1 ? a0/a1 : bitwise_mask(a0);
  }
}

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif
 
#endif

#include <eve/module/core/function/scalar/if_div.hpp>
