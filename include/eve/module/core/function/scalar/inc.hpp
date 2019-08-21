//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_INC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_INC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/as_logical.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto inc_(EVE_SUPPORTS(cpu_)
                                     , T const &a) noexcept
  requires(T, Vectorizable<T>)
  {
    return static_cast<T>(a+One<T>()); 
  }
  
  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<typename U, typename T>
  EVE_FORCEINLINE constexpr auto inc_(EVE_SUPPORTS(cpu_)
                                     , U const & cond
                                     , T const &a) noexcept
  requires(T, Vectorizable<U>, Vectorizable<T>)
  {
    if (std::is_integral_v<T>)
      return static_cast<T>(a-bitwise_mask(T(cond))); 
    else
      return cond ? inc(a) : a;
  } 
}

#endif
