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
    if constexpr (spy::compiler== spy::msvc_) return true;
    else return __has_builtin(__builtin__bwap32);
  }

  constexpr bool has_builtin_swap64(){
    if constexpr (spy::compiler== spy::msvc_) return true;
    else return __has_builtin(__builtin__bwap64);
  }
}
