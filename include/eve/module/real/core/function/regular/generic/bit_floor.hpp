//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/bit_width.hpp>
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
  EVE_FORCEINLINE T bit_floor_(EVE_SUPPORTS(cpu_)
                                 , T const &v) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto vlt1 = v < one(eve::as(v));
      if constexpr(scalar_value<T>) if (vlt1) return zero(eve::as(v));
      if constexpr(floating_real_value<T>)
      {
        auto [m, e] = ifrexp(v);
        e = dec(e);
        auto r = eve::ldexp(one(eve::as(v)), e);
        if constexpr(scalar_value<T>) return r;
        else                          return if_else(vlt1, eve::zero, r);
      }
      else
      {
        using u_t = as_integer_t<T, unsigned>;
        return if_else(is_eqz(v), zero, T{1} << dec(bit_width(bit_cast(v, as<u_t>()))));
//         using elt_t =  element_type_t<T>;
//         auto a = v;
//         a |= bit_shr(a, 1);
//         a |= bit_shr(a, 2);
//         a |= bit_shr(a, 4);
//         if constexpr( sizeof(elt_t) >= 2 )  a |= bit_shr(a,  8);
//         if constexpr( sizeof(elt_t) >= 4 )  a |= bit_shr(a, 16);
//         if constexpr( sizeof(elt_t) >= 8 )  a |= bit_shr(a, 32);
//         a -= (a >> 1);
//         if constexpr(scalar_value<T>) return a;
//         else                          return if_else(vlt1, eve::zero, a);
      }
    }
    else return apply_over(bit_floor, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto bit_floor_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( cond, eve::bit_floor, t);
  }
}
