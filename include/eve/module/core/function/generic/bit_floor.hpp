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
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/ldexp.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto bit_floor_(EVE_SUPPORTS(cpu_)
                                 , T const &v) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto vlt1 = v < One(eve::as(v));
      if constexpr(scalar_value<T>) if (vlt1) return Zero(eve::as(v));
      if constexpr(floating_real_value<T>)
      {
        auto [m, e] = ifrexp(v);
        e = dec(e);
        auto r = eve::ldexp(One(eve::as(v)), e);
        if constexpr(scalar_value<T>) return r;
        else                          return if_else(vlt1, eve::zero_, r);
      }
      else
      {
        using elt_t =  element_type_t<T>;
        auto a = v;
        a |= bit_shr(a, 1);
        a |= bit_shr(a, 2);
        a |= bit_shr(a, 4);
        if constexpr( sizeof(elt_t) >= 2 )  a |= bit_shr(a,  8);
        if constexpr( sizeof(elt_t) >= 4 )  a |= bit_shr(a, 16);
        if constexpr( sizeof(elt_t) >= 8 )  a |= bit_shr(a, 32);
        a -= (a >> 1);
        if constexpr(scalar_value<T>) return a;
        else                          return if_else(vlt1, eve::zero_, a);
      }
    }
    else return apply_over(bit_floor, v);
  }
}

