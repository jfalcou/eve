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

template<simd_value T>
EVE_FORCEINLINE auto
compress_convert_back(auto res, eve::as<T>)
{
  using abi = typename T::abi_type;

  return kumi::map(
      [](auto compressed_count)
      {
        auto [compressed, count] = compressed_count;

        T r;

        constexpr bool is_not_wide_logical = logical_simd_value<T> && abi::is_wide_logical;

        if constexpr( !is_not_wide_logical ) r = eve::bit_cast(compressed, eve::as(r));
        else r = eve::bit_cast(to_logical(compressed), eve::as(r));

        return kumi::tuple {r, count};
      },
      res);
}

template<relative_conditional_expr C, std::unsigned_integral T, std::unsigned_integral U, typename N>
EVE_FORCEINLINE auto
compress_(EVE_SUPPORTS(cpu_), C c, wide<T, N> v, logical<wide<U, N>> mask) noexcept
{
  return compress_using_masks[c](v, mask);
}

template<relative_conditional_expr C, simd_value T, typename U, typename N>
EVE_FORCEINLINE auto
compress_(EVE_SUPPORTS(cpu_), C c, T v, logical<wide<U, N>> m) noexcept
requires(T::size() == N::value)
{
  // canonicalize to reduce duplication in compilation
  if constexpr( !std::unsigned_integral<U> )
  {
    using L1 = logical<wide<make_integer<sizeof(U), unsigned>, N>>;
    return compress(c, v, bit_cast(m, eve::as<L1> {}));
  }
  else if constexpr( logical_value<T> )
  {
    auto bits = compress(c, v.bits(), m);
    return compress_convert_back(bits, eve::as<T> {});
  }
  else
  {
    using e_t1 = make_integer<sizeof(eve::element_type_t<T>), unsigned>;
    using T1   = eve::wide<e_t1, typename T::cardinal_type>;

    auto compressed = compress(c, bit_cast(v, eve::as<T1> {}), m);
    return compress_convert_back(compressed, eve::as<T> {});
  }
}

template<simd_value T, logical_simd_value L>
EVE_FORCEINLINE auto
compress_(EVE_SUPPORTS(cpu_), T v, L mask) noexcept
requires(T::size() == L::size())
{
  return compress[ignore_none](v, mask);
}
}
