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
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

// rotl is only implemented for unsigned integers as per the EVE documentation

namespace eve::detail
{
template<typename T, typename S, typename N, callable_options O>
EVE_FORCEINLINE wide<T,N> rotl_(EVE_REQUIRES(avx512_), O const&, wide<T, N> v, wide<S, N> s) noexcept
  requires(sizeof(T) >= 4 && x86_abi<abi_t<T, N>>)
{
  constexpr auto c = categorize<wide<T, N>>();

  if      constexpr( c == category::uint32x16 ) return _mm512_rolv_epi32 (v, s);
  else if constexpr( c == category::uint32x8  ) return _mm256_rolv_epi32 (v, s);
  else if constexpr( c == category::uint32x4  ) return _mm_rolv_epi32    (v, s);

  else if constexpr( c == category::uint64x8  ) return _mm512_rolv_epi64 (v, s);
  else if constexpr( c == category::uint64x4  ) return _mm256_rolv_epi64 (v, s);
  else if constexpr( c == category::uint64x2  ) return _mm_rolv_epi64    (v, s);
}

template<typename T, auto S, typename N, callable_options O>
EVE_FORCEINLINE wide<T,N> rotl_(EVE_REQUIRES(avx512_), O const&, wide<T, N> v, index_t<S>) noexcept
  requires(sizeof(T) >= 4 && x86_abi<abi_t<T, N>>)
{
  constexpr auto c = categorize<wide<T, N>>();

  if      constexpr( c == category::uint32x16 ) return _mm512_rol_epi32 (v, S);
  else if constexpr( c == category::uint32x8  ) return _mm256_rol_epi32 (v, S);
  else if constexpr( c == category::uint32x4  ) return _mm_rol_epi32    (v, S);

  else if constexpr( c == category::uint64x8  ) return _mm512_rol_epi64 (v, S);
  else if constexpr( c == category::uint64x4  ) return _mm256_rol_epi64 (v, S);
  else if constexpr( c == category::uint64x2  ) return _mm_rol_epi64    (v, S);
}

template<conditional_expr C, typename T, typename S, typename N, callable_options O>
EVE_FORCEINLINE wide<T,N> rotl_(EVE_REQUIRES(avx512_), C const& cx, O const&, wide<T, N> v, wide<S, N> s) noexcept
  requires(sizeof(T) >= 4 && x86_abi<abi_t<T, N>>)
{
  constexpr auto c = categorize<wide<T, N>>();
  auto src = alternative(cx, v, as<wide<T, N>> {});
  auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

  if constexpr( c == category::uint32x16 ) return _mm512_mask_rolv_epi32 (src, m, v, s);
  else if constexpr( c == category::uint32x8  ) return _mm256_mask_rolv_epi32 (src, m, v, s);
  else if constexpr( c == category::uint32x4  ) return _mm_mask_rolv_epi32    (src, m, v, s);

  else if constexpr( c == category::uint64x8  ) return _mm512_mask_rolv_epi64 (src, m, v, s);
  else if constexpr( c == category::uint64x4  ) return _mm256_mask_rolv_epi64 (src, m, v, s);
  else if constexpr( c == category::uint64x2  ) return _mm_mask_rolv_epi64    (src, m, v, s);
}

template<conditional_expr C, typename T, auto S, typename N, callable_options O>
EVE_FORCEINLINE wide<T,N> rotl_(EVE_REQUIRES(avx512_), C const& cx, O const&, wide<T, N> v, index_t<S>) noexcept
  requires(sizeof(T) >= 4 && x86_abi<abi_t<T, N>>)
{
  constexpr auto c = categorize<wide<T, N>>();
  auto src = alternative(cx, v, as<wide<T, N>> {});
  auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

  if constexpr( c == category::uint32x16 ) return _mm512_mask_rol_epi32 (src, m, v, S);
  else if constexpr( c == category::uint32x8  ) return _mm256_mask_rol_epi32 (src, m, v, S);
  else if constexpr( c == category::uint32x4  ) return _mm_mask_rol_epi32    (src, m, v, S);

  else if constexpr( c == category::uint64x8  ) return _mm512_mask_rol_epi64 (src, m, v, S);
  else if constexpr( c == category::uint64x4  ) return _mm256_mask_rol_epi64 (src, m, v, S);
  else if constexpr( c == category::uint64x2  ) return _mm_mask_rol_epi64    (src, m, v, S);
}
}
