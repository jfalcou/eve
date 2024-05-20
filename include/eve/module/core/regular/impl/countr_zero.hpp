//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <bit>

namespace eve::detail
{
  template<value T, callable_options O>
  EVE_FORCEINLINE constexpr T countr_zero_(EVE_REQUIRES(cpu_),
                                           O const&,
                                           T x) noexcept
  {
    if constexpr( scalar_value<T> )
      return T(std::countr_zero(x));
    else
    {
      //      return map(countr_zero, x); // TO DO
      constexpr auto siz = sizeof(eve::element_type_t<T>) * 8;
      using elt_t        = element_type_t<T>;
      x &= eve::inc(~x);
      T c(sizeof(elt_t) * 8 - 1);
      if constexpr( siz == 8 )
      {
        c -= if_else(is_nez(x & T(0x0F)), T(4), zero);
        c -= if_else(is_nez(x & T(0x33)), T(2), zero);
        c -= if_else(is_nez(x & T(0x55)), T(1), zero);
      }
      else if constexpr( siz == 16 )
      {
        c -= if_else(is_nez(x & T(0x00FF)), T(8), zero);
        c -= if_else(is_nez(x & T(0x0F0F)), T(4), zero);
        c -= if_else(is_nez(x & T(0x3333)), T(2), zero);
        c -= if_else(is_nez(x & T(0x5555)), T(1), zero);
      }
      else if constexpr( siz == 32 )
      {
        c -= if_else(is_nez(x & T(0x0000FFFF)), T(16), zero);
        c -= if_else(is_nez(x & T(0x00FF00FF)), T(8), zero);
        c -= if_else(is_nez(x & T(0x0F0F0F0F)), T(4), zero);
        c -= if_else(is_nez(x & T(0x33333333)), T(2), zero);
        c -= if_else(is_nez(x & T(0x55555555)), T(1), zero);
      }
      else if constexpr( siz == 64 )
      {
        c -= if_else(is_nez(x & T(0x00000000FFFFFFFF)), T(32), zero);
        c -= if_else(is_nez(x & T(0x0000FFFF0000FFFF)), T(16), zero);
        c -= if_else(is_nez(x & T(0x00FF00FF00FF00FF)), T(8), zero);
        c -= if_else(is_nez(x & T(0x0F0F0F0F0F0F0F0F)), T(4), zero);
        c -= if_else(is_nez(x & T(0x3333333333333333)), T(2), zero);
        c -= if_else(is_nez(x & T(0x5555555555555555)), T(1), zero);
      }
      return if_else(is_eqz(x), sizeof(elt_t) * 8, c);
    }
  }
}
