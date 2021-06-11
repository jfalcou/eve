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

  constexpr auto int_patterns() {

    constexpr std::array idxs = {0x03020100u, 0x07060504u, 0x0b0a0908u, 0x0f0e0d0cu};

    using row = std::array<std::uint32_t, 4>;

    return std::array {
      row{ idxs[3],       0,       0,       0 },  // 000
      row{ idxs[0], idxs[3],       0,       0 },  // 001
      row{ idxs[1], idxs[3],       0,       0 },  // 010
      row{ idxs[0], idxs[1], idxs[3],       0 },  // 011
      row{ idxs[2], idxs[3],       0,       0 },  // 100
      row{ idxs[0], idxs[2], idxs[3],       0 },  // 101
      row{ idxs[1], idxs[2], idxs[3],       0 },  // 110
      row{ idxs[0], idxs[1], idxs[2], idxs[3] },  // 111
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

    top_bits bits{mask};
    int storage = bits.storage;
    wide<std::uint32_t, eve::fixed<4>> pattern{patterns[storage & 7].data()};
    wide<T, N> shuffled = _mm_shuffle_epi8(v, pattern);
    store(shuffled, ptr);
    return ptr + eve::count_true(mask);
  }
}
