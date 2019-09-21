//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ONEMINUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ONEMINUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/if_else.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/saturated.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto oneminus_(EVE_SUPPORTS(cpu_)
                                          , T const &a) noexcept
  requires(T, Vectorizable<T>)
  {
    return static_cast<T>(One<T>()-a); 
  }
  
   // -----------------------------------------------------------------------------------------------
  // Saturated
  template<typename T>
  EVE_FORCEINLINE auto oneminus_(EVE_SUPPORTS(cpu_)
                                , saturated_type const &
                                , T const &v) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>) return oneminus(v); 
    else if constexpr(std::is_signed_v<T>)
    {
      return (v <= Valmin<T>()+2) ? Valmax<T>() : oneminus(v);
    }                                
    else // if constexpr(std::is_unsigned_v<T>)
    {
      return if_else(v > One(as(v)), eve::zero_, oneminus(v)); 
    }
  }
   
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<typename U, typename T>
  EVE_FORCEINLINE constexpr auto oneminus_(EVE_SUPPORTS(cpu_)
                                          , U const & cond
                                          , T const &a) noexcept
  requires(T, Vectorizable<T>)
  {
    return cond ? oneminus(a) : a;
  }

  // -----------------------------------------------------------------------------------------------
  // Masked Saturated case
  template<typename U, typename T>
  EVE_FORCEINLINE constexpr auto oneminus_(EVE_SUPPORTS(cpu_)
                                          , U const & cond
                                          , saturated_type const &
                                          , T const &v) noexcept
  requires(T, Vectorizable<T>, Vectorizable<U>)
  {
    return cond ? saturated_(oneminus)(v) : v;
  }
 
}

#endif
