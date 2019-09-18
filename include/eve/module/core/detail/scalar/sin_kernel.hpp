//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_SCALAR_SIN_KERNEL_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_SCALAR_SIN_KERNEL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/function/fma.hpp>
#include <type_traits>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto sin_eval( T  z,  T x) noexcept
  requires(T, Floating<T>)
  {
    // here T is float or double and x positive
    static_assert(std::is_floating_point_v<T, double>
                 , "[detail;:sin_kernel] - entry type is not IEEEValue"); 

    if constexpr(std::is_same_v<T, float>)
    {
       T  y1 = horn<T
          , 0xbe2aaaa2
          , 0x3c08839d
          , 0xb94ca1f9
          > (z);
        return fma(y1*z,x,x);
    }
    else // constexpr(std::is_same_v<T, double>)
    {
      T y1 = horn<T,
        0xbfc5555555555548ll,
        0x3f8111111110f7d0ll,
        0xbf2a01a019bfdf03ll,
        0x3ec71de3567d4896ll,
        0xbe5ae5e5a9291691ll,
        0x3de5d8fd1fcf0ec1ll
        > (z);
      return fma(y1*z,x,x);  
    }
  }
}

#endif
