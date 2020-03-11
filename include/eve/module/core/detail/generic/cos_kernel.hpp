//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_GENERIC_COS_KERNEL_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_GENERIC_COS_KERNEL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/mhalf.hpp>
#include <type_traits>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto cos_eval( T  z) noexcept
  {
    using s_t = value_type_t<T>; 
    static_assert(std::is_floating_point_v<s_t>
                 , "[detail;:cos_kernel] - entry type is not IEEEValue"); 

    if constexpr(std::is_same_v<s_t, float>)
    {
      T y = horn<T
        , 0x3d2aaaa5
        , 0xbab60619
        , 0x37ccf5ce
        > (z);
      return inc( fma(z,Mhalf<T>(), y* sqr(z)));
    }
    else // constexpr(std::is_same_v<s_t, double>)
    {
      T y = horn<T,
        0x3fe0000000000000ll,
        0xbfa5555555555551ll,
        0x3f56c16c16c15d47ll,
        0xbefa01a019ddbcd9ll,
        0x3e927e4f8e06d9a5ll,
        0xbe21eea7c1e514d4ll,
        0x3da8ff831ad9b219ll
        > (z);
      return oneminus(y*z);
    }
  }
}

#endif
