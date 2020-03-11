//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_GENERIC_CBRT_KERNEL_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_GENERIC_CBRT_KERNEL_HPP_INCLUDED

#include <type_traits>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fma.hpp> 
#include <eve/function/sqr.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto cbrt_kernel(T xm) noexcept
  requires(T, behave_as<floating_point, T>)
  {
    using vt_t =  value_type_t<T>;
    T u; 
    if constexpr(std::is_same_v<vt_t, double>)
    {
      u = horn < T,
        0x3fd6b69cba168ff2ll, 
        0x3ff8218dde9028b4ll, 
        0xc000eb8277cd8d5dll, 
        0x40039350adad51ecll, 
        0xbffd5ae6cfa20f0cll, 
        0x3fe91e2a6fe7e984ll, 
        0xbfc29801e893366dll 
        >(xm); 
    }
    else
    {
      u = horn < T,
        0x3efc3de2, 
        0x3f3293fa, 
        0xbe441925 
        >(xm); 
    }
    auto t2 = sqr(u) * u;
    auto ym = u * fma(xm, T(2), t2) / fma(T(2), t2, xm); 
    return ym; 
  }
  
}

#endif
