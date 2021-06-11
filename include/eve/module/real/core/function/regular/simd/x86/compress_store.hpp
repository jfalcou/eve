//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <array>

namespace eve::detail
{

  EVE_FORCEINLINE constexpr std::uint32_t add_popcount(std::uint32_t idx, std::uint32_t count)
  {
    return count << 4 | idx;
  }

  EVE_FORCEINLINE constexpr std::uint8_t get_popcount(std::uint8_t idx) {
    return idx >> 4;
  }

  EVE_FORCEINLINE constexpr auto int_patterns() {

    constexpr std::array idxs = {0x03020100u, 0x07060504u, 0x0b0a0908u, 0x0f0e0d0cu};

    using row = std::array<std::uint32_t, 4>;

    return std::array {
      row{ add_popcount(idxs[3], 0),       0,       0,       0 },  // 000
      row{ add_popcount(idxs[0], 1), idxs[3],       0,       0 },  // 001
      row{ add_popcount(idxs[1], 1), idxs[3],       0,       0 },  // 010
      row{ add_popcount(idxs[0], 2), idxs[1], idxs[3],       0 },  // 011
      row{ add_popcount(idxs[2], 1), idxs[3],       0,       0 },  // 100
      row{ add_popcount(idxs[0], 2), idxs[2], idxs[3],       0 },  // 101
      row{ add_popcount(idxs[1], 2), idxs[2], idxs[3],       0 },  // 110
      row{ add_popcount(idxs[0], 3), idxs[1], idxs[2], idxs[3] },  // 111
    };
  }

  template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(ssse3_),
                     unsafe_type,
                     wide<T, N> v,
                     logical<wide<T, N>> mask,
                     Ptr ptr) noexcept
    requires (N() == 4 && std::same_as<T, std::int32_t> )
  {
    constexpr auto patterns = int_patterns();

    top_bits mmask{mask};
    wide<std::uint32_t, eve::fixed<4>> pattern{patterns[mmask.as_int() & 7].data()};

    auto byte_idxs = eve::bit_cast(pattern, eve::as_<wide<std::uint8_t, eve::fixed<16>>>{});

    int popcount_3 = get_popcount(byte_idxs.get(0));
    int popcount_4 = popcount_3 + mmask.get(3);

    wide<T, N> shuffled = _mm_shuffle_epi8(v, pattern);
    store(shuffled, ptr);
    return ptr + popcount_4;
  }
}
