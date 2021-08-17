//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/sqr.hpp>
#include <type_traits>
#include <eve/module/real/core/detail/generic/horn.hpp>
#include <eve/module/real/core/detail/generic/horn1.hpp>  

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto tancot_eval( const T & z) noexcept
  {
    // here T is float or double and z positive
    static_assert(std::is_floating_point_v<value_type_t<T>>
                 , "[detail;:tan_kernel] - entry type is not IEEEValue"); 
    if constexpr(std::is_same_v<value_type_t<T>, float>)
    {
      T zz = eve::sqr(z);
      return fma(horn<T
                , 0x3eaaaa6fu
                , 0x3e0896ddu
                , 0x3d5ac5c9u
                , 0x3cc821b5u
                , 0x3b4c779cu
                , 0x3c19c53bu>(zz), zz*z, z);   
    }
    else if constexpr(std::is_same_v<value_type_t<T>, double>)
    {
      T zz = sqr(z);
      const T num = horn<T,
        0xc1711fead3299176ull,
        0x413199eca5fc9dddull,
        0xc0c992d8d24f3f38ull
        >(zz);
      T den = horn1<T,
        0xc189afe03cbe5a31ull,
        0x4177d98fc2ead8efull,
        0xc13427bc582abc96ull,
        0x40cab8a5eeb36572ull
        //    0x3ff0000000000000ull
        >(zz);
      return fma(z, (zz*(num/den)), z);   
    }
  }
}

