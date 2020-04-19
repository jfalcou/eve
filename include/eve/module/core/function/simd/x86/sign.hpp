//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SIGN_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/binarize.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<integral_real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> sign_(EVE_SUPPORTS(ssse3_)
                                        , wide<T, N, sse_> const &a) noexcept
  {
    if constexpr(std::is_signed_v<T>)
    {
      using t_t = wide<T, N, sse_>;
      if constexpr(sizeof(T) == 1)
        return t_t(_mm_sign_epi8(One(as(a)), a));
      else if constexpr(sizeof(T) == 2)
        return t_t(_mm_sign_epi16(One(as(a)), a));
      else if constexpr(sizeof(T) == 4)
        return t_t(_mm_sign_epi32(One(as(a)), a));
      else if constexpr(sizeof(T) == 8)
        return map(sign, a);
    }
    else
      return binarize(is_nez(a));
  }
}

#endif
