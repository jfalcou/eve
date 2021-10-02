//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/function/compress_store_swizzle_mask_num.hpp>

#include <eve/function/if_else.hpp>
#include <eve/function/slide_left.hpp>

namespace eve::detail
{
  // See comments in compress_store_num and x86 impl

  template <typename N>
  EVE_FORCEINLINE eve::wide<std::uint8_t, N>
  byte_shuffle(eve::wide<std::uint8_t, N> what, eve::wide<std::uint8_t, N> pattern)
  {
         if constexpr ( N() <= 8 ) return vtbl1_u8  (what, pattern);
    else if constexpr ( eve::current_api == eve::asimd ) return vqtbl1q_u8(what, pattern);
    else
    {
      uint8x8x2_t lh  = {{ vget_low_u8(what), vget_high_u8(what) }};
      return vcombine_u8(
        vtbl2_u8(lh, vget_low_u8(pattern)), vtbl2_u8(lh, vget_high_u8(pattern))
      );
    }
  }

  template <typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(neon128_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr)
    requires arm_abi<abi_t<T, N>> && ( N() == 4 )
  {
    using u_t   = eve::as_integer_t<T, unsigned>;
    using bytes = typename wide<T, N>::template rebind<std::uint8_t, fixed<sizeof(T) * 4>>;

    auto [num, count] = compress_store_swizzle_mask_num[ignore_none](mask);

    // load pattern
    u_t const* pattern_p = pattern_4_elements_bytes_v<u_t>[num].data();
    auto     * bytes_p   = (std::uint8_t const*) (pattern_p);
    auto       bytes_ap  = eve::as_aligned(bytes_p, eve::fixed<bytes::size()>{});
    bytes pattern{bytes_ap};

    bytes bytes_v = bit_cast(v, eve::as<bytes>{});
    bytes_v       = byte_shuffle(bytes_v, pattern);
    v             = bit_cast(bytes_v, as(v));

    store(v, ptr);
    return as_raw_pointer(ptr) + count;
  }

  template <typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(neon128_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr)
    requires arm_abi<abi_t<T, N>> && ( N() == 8 ) && (sizeof(T) == 2)
  {
    using u_t   = eve::as_integer_t<T, unsigned>;
    using bytes = typename wide<T, N>::template rebind<std::uint8_t, fixed<sizeof(T) * 8>>;

    // Reduce variations: in each pair from 4 to 3. 10 and 01 become the same.
    // Two last elements don't matter.
    auto to_left = eve::slide_left(v, eve::index<1>);
    v = eve::if_else[mask]( v, to_left );

    // Find pattern
    auto [num, count] = compress_store_swizzle_mask_num(mask);

    u_t const* pattern_p = pattern_8_elements_bytes_v<u_t>[num].data();
    auto     * bytes_p   = (std::uint8_t const*) (pattern_p);
    auto       bytes_ap  = eve::as_aligned(bytes_p, eve::fixed<bytes::size()>{});
    bytes pattern{bytes_ap};

    // Shuffle
    bytes bytes_v = bit_cast(v, eve::as<bytes>{});
    bytes_v       = byte_shuffle(bytes_v, pattern);
    v             = bit_cast(bytes_v, as(v));

    // store
    store(v, ptr);
    return as_raw_pointer(ptr) + count;
  }
}
