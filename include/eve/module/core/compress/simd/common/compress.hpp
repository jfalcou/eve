//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/compress/detail/compress_using_masks.hpp>

namespace eve::detail
{

template<relative_conditional_expr C, typename T, typename U, typename N>
EVE_FORCEINLINE auto
compress_(EVE_SUPPORTS(cpu_), C c, wide<T, N> v, logical<wide<U, N>> mask) noexcept
{
  if constexpr( C::is_complete && !C::is_inverted )
  {
    kumi::tuple cur {v, (std::ptrdiff_t)0};
    return kumi::tuple<decltype(cur)> {cur};
  }
  else return compress_using_masks[c](v, mask);
}

template<typename L> struct compress_bits_to_logical
{
  // unfortunately, we are not consistent with integer types
  template<typename T, typename N, std::integral I>
  EVE_FORCEINLINE auto operator()(kumi::tuple<wide<T, N>, I> bits_offset)
  {
    auto [bits, offset] = bits_offset;

    eve::as_wide_t<eve::element_type_t<L>, N> r;

    if constexpr( abi_t<T, N>::is_wide_logical ) r = bit_cast(bits, as{r});
    else r = bit_cast(to_logical(bits), as{r});

    return kumi::tuple {r, offset};
  }
};

template<relative_conditional_expr C, logical_simd_value T, logical_simd_value L>
EVE_FORCEINLINE auto
compress_(EVE_SUPPORTS(cpu_), C c, T v, L mask) noexcept
requires(T::size() == L::size())
{
  auto compressed = compress[c](v.bits(), mask);
  return kumi::map(compress_bits_to_logical<T> {}, compressed);
}

template<relative_conditional_expr C, simd_value T, logical_simd_value L>
EVE_FORCEINLINE auto
compress_(EVE_SUPPORTS(cpu_), C, T, L) noexcept
requires(T::size() == L::size()) && (has_bundle_abi_v<T>)
{
  static_assert(!has_bundle_abi_v<T>, "FIX: 1647, eve::compress does not support bundle at the moment.");
}

template<simd_value T, logical_simd_value L>
EVE_FORCEINLINE auto
compress_(EVE_SUPPORTS(cpu_), T v, L mask) noexcept
requires(T::size() == L::size())
{
  return compress[ignore_none](v, mask);
}
}
