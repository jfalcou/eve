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

  // The idea from: https://gist.github.com/aqrit/6e73ca6ff52f72a2b121d584745f89f3#file-despace-cpp-L141
  // Was shown to me by: @aqrit
  // Stack Overflow discussion: https://chat.stackoverflow.com/rooms/212510/discussion-between-denis-yaroshevskiy-and-peter-cordes
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
                     unsafe_type u,
                     wide<T, N> v,
                     logical<wide<T, N>> mask,
                     Ptr ptr) noexcept
  {
    if constexpr ( std::floating_point<T> )
    {
      using i_t = eve::as_integer_t<T>;
      auto  i_p = ptr_cast<i_t>(ptr);
      auto  i_v = eve::bit_cast(v, eve::as_<wide<i_t, N>>{});
      auto  i_m = eve::bit_cast(mask, eve::as_<eve::logical<wide<i_t, N>>>{});

      i_t* stored = unsafe(compress_store)(i_v, i_m, i_p);
      return (T*) stored;
    }
    else if constexpr ( N() == 4 && sizeof(T) == 4 )
    {
      alignas(16) auto patterns = int_patterns();

      top_bits mmask{mask};

      aligned_ptr<std::uint32_t, 16> pattern_ptr{patterns[mmask.as_int() & 7].data()};
      wide<std::uint32_t, eve::fixed<4>> pattern{pattern_ptr};

      auto byte_idxs = eve::bit_cast(pattern, eve::as_<wide<std::uint8_t, eve::fixed<16>>>{});
      wide<T, N> shuffled = _mm_shuffle_epi8(v, pattern);

      int popcount = get_popcount(byte_idxs.get(0)) + mmask.get(3);

      store(shuffled, ptr);
      return as_raw_pointer(ptr) + popcount;
    }
    else return compress_store_(EVE_RETARGET(cpu_), u, v, mask);
  }
}
