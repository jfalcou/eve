//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/convert.hpp>
#include <eve/detail/function/compress_store_swizzle_mask_num.hpp>
#include <eve/function/count_true.hpp>
#include <eve/function/unalign.hpp>

#include <eve/detail/function/compress_store_impl_switch.hpp>

#include <array>
#include <bit>

// sse2/sse3 ---------------------------------------------------------
// switch based implementation

namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(sse2_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires (current_api < ssse3)
  {
    return compress_store_impl_switch[c](v, mask, ptr);
  }
}

// ssse3 -> avx2 (no bmi) ---------------------------------------------------------
// mask based (@aqrit from StackOverflow's idea)
namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(sse4_1_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && ( N() == 4 )
  {
    return compress_store_impl_using_masks(c, v, mask, ptr);
  }

  template<typename T, typename U, typename N, typename Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(sse4_1_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && ( N() == 4 )
  {
    if constexpr ( N() == 4 && sizeof(T) == 8 && current_api == avx  )
    {
      return compress_store_impl_aggregated(v, mask, ptr);
    }
    else return compress_store_impl[eve::ignore_none](v, mask, ptr);
  }

  template<typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(ssse3_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && (current_api <= avx2) && ( N() == 8 )
  {
    return compress_store_impl_using_masks(eve::ignore_none, v, mask, ptr);
  }

  template<typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(ssse3_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && (current_api <= avx2) && ( N() == 16 )
  {
    using half_wide = wide<T, eve::fixed<8>>;

    if constexpr ( sizeof(T) == 2 )
    {
      auto [l, h] = [&] {
        if constexpr ( current_api == avx2 )
        {
          wide<T, N> to_left =  _mm256_shufflehi_epi16(v,       _MM_SHUFFLE(0, 3, 2, 1));
                     to_left =  _mm256_shufflelo_epi16(to_left, _MM_SHUFFLE(0, 3, 2, 1));
          v = eve::if_else[mask](v, to_left);
          return v.slice();
        }
        else
        {
          auto [l, h] = v.slice();
          auto [ml, mh] = mask.slice();
          half_wide l_to_left = _mm_bsrli_si128(l, 2);
          half_wide h_to_left = _mm_bsrli_si128(h, 2);
          l = eve::if_else[ml](l, l_to_left);
          h = eve::if_else[mh](h, h_to_left);
          return std::pair{l, h};
        }
      }();

      using pattern8 = typename wide<T, N>::template rebind<std::uint16_t, eve::fixed<8>>;

      auto [lo_idx, lo_count, hi_idx, hi_count] = compress_store_swizzle_mask_num(mask);

      auto lo_shuffle_ptr = eve::as_aligned(pattern_8_elements_bytes_v<std::uint16_t>[lo_idx].data(), eve::lane<8>);
      auto hi_shuffle_ptr = eve::as_aligned(pattern_8_elements_bytes_v<std::uint16_t>[hi_idx].data(), eve::lane<8>);

      pattern8 lo_shuffle{lo_shuffle_ptr};
      pattern8 hi_shuffle{hi_shuffle_ptr};

      l = _mm_shuffle_epi8(l, lo_shuffle);
      h = _mm_shuffle_epi8(h, hi_shuffle);
      eve::store(l, ptr);

      T* res = unalign(ptr) + lo_count;
      eve::store(h, res);
      return res + hi_count;
    }
    else if constexpr ( sizeof(T) == 1 )
    {
      using pattern8 = typename wide<T, N>::template rebind<std::uint8_t, eve::fixed<8>>;

      eve::wide<T, N> to_left = _mm_bsrli_si128(v, 1);
      v = eve::if_else[mask]( v, to_left );

      auto [lo_idx, lo_count, hi_idx, hi_count] = compress_store_swizzle_mask_num(mask);

      pattern8 lo_shuffle{pattern_8_elements_bytes_v<std::uint8_t>[lo_idx].data()};
      pattern8 hi_shuffle{pattern_8_elements_bytes_v<std::uint8_t>[hi_idx].data()};
      hi_shuffle |= pattern8{0x08};  // adjust higher idxs +8

      T* res = unalign(ptr);
      _mm_storel_epi64((__m128i*)res, _mm_shuffle_epi8(v, lo_shuffle));
      res += lo_count;
      _mm_storel_epi64((__m128i*)res, _mm_shuffle_epi8(v, hi_shuffle));
      return res + hi_count;
    }
  }
}
