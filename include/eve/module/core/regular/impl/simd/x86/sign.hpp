//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/one.hpp>

#include <type_traits>

namespace eve::detail
{
template<integral_scalar_value T, typename N, callable_options O>
EVE_FORCEINLINE wide<T, N> sign_(EVE_REQUIRES(ssse3_),
                                 O const & o,
                                 wide<T, N> a) noexcept
requires x86_abi<abi_t<T, N>>
{
  constexpr auto c    = categorize<wide<T, N>>();
  constexpr auto tgt  = eve::as(a);

  if constexpr(current_api >= avx512 || sizeof(T) == 8)               return sign.behavior(cpu_{}, o, a);
  else if constexpr( current_api >= avx2 && c == category::int32x8 )  return _mm256_sign_epi32(one(tgt), a);
  else if constexpr( current_api >= avx2 && c == category::int32x8 )  return _mm256_sign_epi32(one(tgt), a);
  else if constexpr( current_api >= avx2 && c == category::int16x16)  return _mm256_sign_epi16(one(tgt), a);
  else if constexpr( current_api >= avx2 && c == category::int8x32 )  return _mm256_sign_epi8 (one(tgt), a);
  else if constexpr( current_api >= avx && N::value > 1)
  {
    auto[l,h] = a.slice();
    return wide<T,N>(sign(l),sign(h));
  }
  else if constexpr( current_api >= ssse3 && c == category::int32x4 ) return _mm_sign_epi32(one(tgt), a);
  else if constexpr( current_api >= ssse3 && c == category::int16x8 ) return _mm_sign_epi16(one(tgt), a);
  else if constexpr( current_api >= ssse3 && c == category::int8x16 ) return _mm_sign_epi8(one(tgt), a);
  else if constexpr( current_api >= sse2 )                            return (a >> sizeof(T)*8) - (a > 0).mask();
  else return sign.behavior(cpu_{}, o, a);
}
}
