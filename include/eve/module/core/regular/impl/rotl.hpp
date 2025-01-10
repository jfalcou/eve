//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename S, callable_options O>
  constexpr EVE_FORCEINLINE as_wide_as_t<T,S> rotl_(EVE_REQUIRES(cpu_), O const& o, T v, S s)
  {
    if constexpr(scalar_value<S>)
    {
      constexpr S width = sizeof(element_type_t<T>) * 8 - 1;
      int         n     = s & width;

      if( n >= 0 ) return (v << n) | (v >> (-n & width));
      else         return (v << n) | (v >> n);
    }
    else if constexpr (scalar_value<T>) return rotl[o](as_wide_as_t<T,S>(v), s);
    else                                return map(rotl[o], v, s);
  }

  template<typename T, auto S, callable_options O>
  constexpr EVE_FORCEINLINE T rotl_(EVE_REQUIRES(cpu_), O const& o, T v, index_t<S>)
  {
    return rotl[o](v, S);
  }
}
