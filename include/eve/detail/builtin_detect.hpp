//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{

  constexpr bool has_builtin_swap32(){
    constexpr bool b = __has_builtin(__builtin_bswap32) || __has_builtin(_byteswap_ulong);
    return b;
  }

  constexpr bool has_builtin_swap64(){
    constexpr bool b = __has_builtin(__builtin_bswap64)|| __has_builtin(_byteswap_uint64);
    return b;
  }
}
