//==================================================================================================
/*
   EVE - Expressive Vector Engine
   Copyright : EVE Contributors & Maintainers
   SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<unsigned_value T>
  EVE_FORCEINLINE constexpr T fls_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr(has_native_abi_v<T>)
    {
      T aa = a0|one(as(a0));
      if constexpr((sizeof(elt_t)) == 8)
      {
        if constexpr(scalar_value<T>)
        {
          auto ahi = a0 >> 32;
          if (is_nez(ahi)) return 32ul+fls(uint32(ahi));
          auto alo = uint32(a0-(ahi << 32));
          return T(fls(alo));
        }
        else
          return map(fls, a0);
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
    else return apply_over(fls, a0);
  }
}
