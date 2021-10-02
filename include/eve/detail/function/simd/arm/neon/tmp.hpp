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
  template <typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(neon128_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr)
    requires arm_abi<abi_t<T, N>> && ( N() == 4 ) && std::same_as<T, int>
  {
    using u_t   = eve::as_integer_t<T, unsigned>;
    using bytes = typename wide<T, N>::template rebind<std::uint8_t, fixed<16>>;

    alignas(sizeof(T) * 4) auto patterns = pattern_4_elements(idxs_bytes<u_t>);

    int bits = compress_store_swizzle_mask_num[ignore_none](mask);
    int num = bits & 7;

    // load pattern
    u_t const* pattern_p = patterns[num].data();
    auto     * bytes_p   = (std::uint8_t const*) (pattern_p);
    auto       bytes_ap  = eve::as_aligned(bytes_p, eve::fixed<bytes::size()>{});
    bytes pattern{bytes_ap};

    bytes bytes_v = bit_cast(v, eve::as<bytes>{});
          bytes_v = vqtbl1q_u8(bytes_v, pattern);

    v = bit_cast(bytes_v, as(v));

    store(v, ptr);
    return as_raw_pointer(ptr) + std::popcount(static_cast<std::uint32_t>(bits));
  }
}
