//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_MANHATTAN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_MANHATTAN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/inf.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  manhattan_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1) noexcept
  requires std::floating_point<T>
  {
    return eve::abs(a0)+eve::abs(a1);
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  manhattan_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1, T const &a2) noexcept
  requires std::floating_point<T>
  {
    return eve::abs(a0)+eve::abs(a1)+ eve::abs(a2);
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  manhattan_(EVE_SUPPORTS(cpu_)
            ,  pedantic_type const &
            , T const &a0
            , T const &a1) noexcept
  requires std::floating_point<T>
  {
    if constexpr(eve::platform::supports_invalids)
    {
      if (is_infinite(a1) || is_infinite(a0)) return Inf<T>();
    }
    return eve::abs(a0)+eve::abs(a1); 
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  manhattan_(EVE_SUPPORTS(cpu_)
            ,  pedantic_type const &
            , T const &a0
            , T const &a1
            , T const &a2 ) noexcept
  requires std::floating_point<T>
  {
    if constexpr(eve::platform::supports_invalids)
    {
      if (is_infinite(a2) || is_infinite(a1) || is_infinite(a0)) return Inf<T>();
    }
    return eve::abs(a0)+eve::abs(a1)+ eve::abs(a2);
  }   
}

#endif
