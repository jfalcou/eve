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
#include <eve/module/core/regular/if_else.hpp>

#include <concepts>

namespace eve::detail
{

template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                sub_(EVE_SUPPORTS(sse2_),
                     saturated_type st,
                     wide<T, N>     v0,
                     wide<T, N>     v1) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( std::is_floating_point_v<T> ) return sub(v0, v1);
  else if constexpr( c == category::int16x32 ) return _mm512_subs_epi16(v0, v1);
  else if constexpr( c == category::uint16x32 ) return _mm512_subs_epu16(v0, v1);
  else if constexpr( c == category::int8x64 ) return _mm512_subs_epi8(v0, v1);
  else if constexpr( c == category::uint8x64 ) return _mm512_subs_epu8(v0, v1);
  else if constexpr( current_api >= avx2 && c == category::int16x16 )
    return _mm256_subs_epi16(v0, v1);
  else if constexpr( current_api >= avx2 && c == category::uint16x16 )
    return _mm256_subs_epu16(v0, v1);
  else if constexpr( current_api >= avx2 && c == category::int8x32 )
    return _mm256_subs_epi8(v0, v1);
  else if constexpr( current_api >= avx2 && c == category::uint8x32 )
    return _mm256_subs_epu8(v0, v1);
  else if constexpr( c == category::int16x8 ) return _mm_subs_epi16(v0, v1);
  else if constexpr( c == category::uint16x8 ) return _mm_subs_epu16(v0, v1);
  else if constexpr( c == category::int8x16 ) return _mm_subs_epi8(v0, v1);
  else if constexpr( c == category::uint8x16 ) return _mm_subs_epu8(v0, v1);
  else return sub_(EVE_RETARGET(cpu_), st, v0, v1);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                sub_(EVE_SUPPORTS(sse2_),
                     C const                         &cx,
                     saturated_type    st,
                     wide<T, N> const                &v,
                     wide<T, N> const                &w) noexcept requires x86_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( C::is_complete || abi_t<T, N>::is_wide_logical )
  {
    return sub_(EVE_RETARGET(cpu_), cx, st, v, w);
  }
  else
  {
    auto src = alternative(cx, v, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr( std::is_floating_point_v<T> ) return sub[cx](v, w);
    else if constexpr( c == category::int16x32 ) return _mm512_mask_subs_epi16(src, m, v, w);
    else if constexpr( c == category::uint16x32 ) return _mm512_mask_subs_epu16(src, m, v, w);
    else if constexpr( c == category::int8x64 ) return _mm512_mask_subs_epi8(src, m, v, w);
    else if constexpr( c == category::uint8x64 ) return _mm512_mask_subs_epu8(src, m, v, w);
    else if constexpr( current_api >= avx2 && c == category::int16x16 )
      return _mm256_mask_subs_epi16(src, m, v, w);
    else if constexpr( current_api >= avx2 && c == category::uint16x16 )
      return _mm256_mask_subs_epu16(src, m, v, w);
    else if constexpr( current_api >= avx2 && c == category::int8x32 )
      return _mm256_mask_subs_epi8(src, m, v, w);
    else if constexpr( current_api >= avx2 && c == category::uint8x32 )
      return _mm256_mask_subs_epu8(src, m, v, w);
    else if constexpr( c == category::int16x8 ) return _mm_mask_subs_epi16(src, m, v, w);
    else if constexpr( c == category::uint16x8 ) return _mm_mask_subs_epu16(src, m, v, w);
    else if constexpr( c == category::int8x16 ) return _mm_mask_subs_epi8(src, m, v, w);
    else if constexpr( c == category::uint8x16 ) return _mm_mask_subs_epu8(src, m, v, w);
    else return if_else(cx, eve::sub(st, v, w), src);
  }
}

}
