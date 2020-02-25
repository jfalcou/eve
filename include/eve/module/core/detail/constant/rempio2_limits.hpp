//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_CONSTANT_REMPIO2_LIMITS_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_CONSTANT_REMPIO2_LIMITS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/valmax.hpp>

namespace eve::detail
{
  template <typename D, typename T>
  EVE_FORCEINLINE auto Rempio2_limit(D const &, const T &) noexcept
  {
    if constexpr(std::is_same_v<D, restricted_type>)
    {
      return Pio_4<T>();
    }    
    if constexpr(std::is_same_v<D, small_type>)
    {
      return Ieee_constant<T, 0x42f00000U, 0X419921FB38000000ULL>(); //120, 105414350
    }
    else  if constexpr(std::is_same_v<D, medium_type>)
    {
      return Ieee_constant<T, 0X58D6DE3DU, 0X42F0000000000000ULL>(); // 1889999955951616, 281474976710656, 
    }
    else
    {
      return Valmax<T>(); 
    }
  }
}

#endif
