//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ROUND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ROUND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/nearest.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T round_(EVE_SUPPORTS(cpu_)
                                    , T const &a) noexcept
  {
    return eve::nearest(a); 
  }
  
  template<typename TAG, typename T>
  EVE_FORCEINLINE constexpr T round_(EVE_SUPPORTS(cpu_)
                                    , TAG   const &
                                    , T const &a) noexcept
  {
    if constexpr(std::is_same_v<TAG, eve::up_type>) return eve::ceil(a);
    if constexpr(std::is_same_v<TAG, eve::down_type>) return eve::floor(a);
    if constexpr(std::is_same_v<TAG, eve::to_zero_type>) return eve::trunc(a);
    if constexpr(std::is_same_v<TAG, eve::nearest_int_type>) return eve::nearest(a);
  }
}

#endif
