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

  constexpr inline bool has_builtin_swap32(){
    return (spy::compiler== spy::msvc_
               || spy::compiler== spy::gcc_
               || spy::compiler== spy::clang_);
  }

  auto inline builtin_bswap32(auto x) noexcept
  {
    if constexpr(spy::compiler== spy::msvc_) return _bswap_ulong(x);
    else return __builtin_bswap32(x);
  }

  constexpr inline  bool has_builtin_swap64(){
    return (spy::compiler== spy::msvc_
               || spy::compiler== spy::gcc_
               || spy::compiler== spy::clang_);
  }

  auto inline builtin_bswap64(auto x) noexcept
  {
    if constexpr(spy::compiler== spy::msvc_) return _bswap_uint64(x);
    else return __builtin_bswap64(x);
  }

}
