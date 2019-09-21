//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ACOSD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ACOSD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/acos.hpp>
#include <eve/function/indeg.hpp>
#include <eve/function/pedantic.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto acosd_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
    return indeg(acos(a0)); 
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto acosd_(EVE_SUPPORTS(cpu_)
                                  , pedantic_type const &      
                                  , T const &a0) noexcept
  {
    return indeg(eve::pedantic_(acos)(a0)); 
  } 
}

#endif
