//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<unsigned_value T>
  EVE_FORCEINLINE constexpr T ffs_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if (is_eqz(a0)) return sizeof(T)*8;
        if constexpr(sizeof(T) == 8)      return  dec(__builtin_ffsll(a0));
        else if constexpr(sizeof(T) == 4) return  dec(__builtin_ffs(a0));
        else                              return  dec(T(__builtin_ffs(uint32_t(a0))));
      }
      else
      {
        //       auto n = T(sizeof(elt_t)*8);
        auto aa = a0|one(as(a0));
        if constexpr(sizeof(elt_t) == 8)
        {
          return map(ffs, aa);
        }
        else if constexpr(sizeof(elt_t) == 4)
        {
          auto da = float64(aa);
          return uint32(exponent(da));
        }
        else  if constexpr(sizeof(elt_t) == 2)
        {
          auto da = float32(aa);
          return uint16(exponent(da));
        }
         else  if constexpr(sizeof(elt_t) == 1)
        {
          auto da = float32(aa);
          return uint8(exponent(da));
        }
     }
    }
    else return apply_over(ffs, a0);
  }

}
