//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <bit>
#include <utility>

#include <eve/detail/function/compress_store_swizzle_mask_num.hpp>

namespace eve::detail
{
  // Not quite the same as x86 but on arm we have to clean up the top bits in the shuffle.
  constexpr std::uint32_t add_popcount(std::uint32_t pattern, std::uint32_t count)
  {
    return count << 28 | pattern;
  }

  constexpr auto split_into_count_and_pattern (std::uint32_t pattern) {
    return std::pair { pattern & (1 << 28 - 1), (pattern >> 28)};
  }

  constexpr std::uint32_t pattern_4_elements(std::uint32_t bits)
  {
    // last element always set
    std::uint32_t res = 3;

    // element 2
    if (bits & (1 << 2))
    {
      res <<= 8;
      res += 2;
    }

    // element 1
    if (bits & (1 << 1))
    {
      res <<= 8;
      res += 1;
    }

    // element 0
    if (bits & 1)
    {
      res <<= 8;
    }

    add_popcount(res, std::popcount(bits));
    return res;
  }

  EVE_FORCEINLINE constexpr auto pattern_4_elements()
  {
    return std::array {
      pattern_4_elements(0b000),
      pattern_4_elements(0b001),
      pattern_4_elements(0b010),
      pattern_4_elements(0b011),
      pattern_4_elements(0b100),
      pattern_4_elements(0b101),
      pattern_4_elements(0b110),
      pattern_4_elements(0b111),
    };
  }

  template <typename U, typename N>
  EVE_FORCEINLINE auto compress_store_pattern_count_4(logical<wide<U, N>> mask)
  {
    constexpr std::array patterns = pattern_4_elements();
    const [pattern_num, last_set] = compress_store_swizzle_mask_num(mask);
    auto  [pattern, count]        = split_into_count_and_pattern(patterns[pattern_num]);

    count += (last_set) ? 1 : 0;

    using bytes_4_t = typename wide<T, N>::template rebind<std::uint8_t, eve::fixed<4>>;
    return std::pair{bytes_4_t{&pattern}, count};
  }

  template <typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(neon_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr)
    requires arm_abi<abi_t<T, N>> && ( N() == 4 ) && std::same_as<T, int>
  {
    auto [pattern, count] = compress_store_pattern_count_4(mask);
    auto spread = eve::convert(pattern, eve::as<std::uint32_t>{});
    u32x4 idxs  = vmulq_n_u32(spread, 0x03020100);

  }
}
