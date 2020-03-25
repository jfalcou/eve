//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ASEC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ASEC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/acos.hpp>
#include <eve/function/raw.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto asec_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  Requires(T, floating_point<value_type_t<T>>)
  {
    return acos(rec(a0)); 
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto asec_(EVE_SUPPORTS(cpu_)
                                  , raw_type const &     
                                  , T const &a0) noexcept
  Requires(T, floating_point<value_type_t<T>>)
  {
    return raw_(acos)(rec(a0)); 
  }

}

#endif
