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
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/meta.hpp>
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
  // Masked case
  template<typename U, typename T>
  EVE_FORCEINLINE constexpr auto oneminus_(EVE_SUPPORTS(cpu_)
                                          , U const & cond
                                          , T const &a) noexcept
  requires(T, Vectorizable<T>)
  {
    return cond ? oneminus(a) : a;
  } 
}

#endif
