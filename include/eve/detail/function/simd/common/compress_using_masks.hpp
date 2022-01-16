//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/traits/max_scalar_size.hpp>

#include <eve/detail/compress/mask_num.hpp>
#include <eve/detail/function/byte_16_runtime_shuffle.hpp>

#include <eve/function/count_true.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/slide_left.hpp>
#include <eve/function/zip.hpp>

#include <bit>

namespace eve::detail
{
// permutation masks ------------------

  template <std::unsigned_integral T>
  EVE_FORCEINLINE constexpr auto pattern_4_elements(std::array<T, 8> idxs)
  {
    using row = std::array<T, 4>;

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

  // See compress_store_num for explanation
  template <std::unsigned_integral T>
  EVE_FORCEINLINE constexpr auto pattern_8_elements(std::array<T, 8> idxs)
  {
    using row = std::array<T, 8>;

    std::array<row, 27> res = {};

    for (unsigned i = 0; i != 27; ++i)
    {
      unsigned number_of_9s = 0, number_of_3s = 0, number_of_1s = 0;
      unsigned base_3_value = i;

      if (base_3_value >= 9) ++number_of_9s, base_3_value -= 9;
      if (base_3_value >= 9) ++number_of_9s, base_3_value -= 9;
      if (base_3_value >= 3) ++number_of_3s, base_3_value -= 3;
      if (base_3_value >= 3) ++number_of_3s, base_3_value -= 3;
      if (base_3_value >= 1) ++number_of_1s, base_3_value -= 1;
      if (base_3_value >= 1) ++number_of_1s, base_3_value -= 1;

      auto* it = res[i].begin();
      if (number_of_1s) *it++ = idxs[0], --number_of_1s;
      if (number_of_1s) *it++ = idxs[1], --number_of_1s;
      if (number_of_3s) *it++ = idxs[2], --number_of_3s;
      if (number_of_3s) *it++ = idxs[3], --number_of_3s;
      if (number_of_9s) *it++ = idxs[4], --number_of_9s;
      if (number_of_9s) *it++ = idxs[5], --number_of_9s;
      *it++ = idxs[6];
      *it++ = idxs[7];
    }

    return res;
  }

  template <std::unsigned_integral T>
  constexpr auto idxs_bytes = [] {
    std::array<T, 8> res = {};

    // ppc is bigendian
    constexpr bool is_le = std::endian::native == std::endian::little;

    for (unsigned i = 0; i != 8; ++i)
    {
      unsigned byte_idx = i * sizeof(T);

      if constexpr ( sizeof(T) == 4 )
      {
        if constexpr ( is_le ) res[i] = (byte_idx + 3) << 24 | (byte_idx + 2) << 16 | (byte_idx + 1) << 8 | byte_idx;
        else                   res[i] = (byte_idx    ) << 24 | (byte_idx + 1) << 16 | (byte_idx + 2) << 8 | (byte_idx + 3);
      }
      else if constexpr ( sizeof(T) == 2 )
      {
        if constexpr ( is_le ) res[i] = (byte_idx + 1) << 8 | (byte_idx    );
        else                   res[i] = (byte_idx    ) << 8 | (byte_idx + 1);
      }
      else if constexpr ( sizeof(T) == 1 )
      {
        res[i] = byte_idx;
      }
    }

    return res;
  }();

  template <std::unsigned_integral T>
  constexpr auto pattern_4_elements_bytes_v alignas(sizeof(T) * 4) =
    pattern_4_elements(idxs_bytes<T>);

  template <std::unsigned_integral T>
  constexpr auto pattern_8_elements_bytes_v alignas(sizeof(T) * 8) =
    pattern_8_elements(idxs_bytes<T>);

  template <typename T, typename N>
  EVE_FORCEINLINE
  auto compress_using_masks_shuffle_(EVE_SUPPORTS(cpu_), wide<T, N> v, std::ptrdiff_t num) noexcept
  {
    if constexpr ( kumi::product_type<T> )
    {
      return wide<T, N>{ kumi::map(compress_using_masks_shuffle, v, num) };
    }
    else
    {
      using u_t   = eve::as_integer_t<T, unsigned>;
      using bytes = typename wide<T, N>::template rebind<std::uint8_t, fixed<sizeof(T) * N()>>;

      if constexpr ( N() == 4 )
      {
        u_t const* pattern_p = pattern_4_elements_bytes_v<u_t>[num].data();
        auto     * bytes_p   = (std::uint8_t const*) (pattern_p);
        auto       bytes_ap  = eve::as_aligned(bytes_p, eve::fixed<bytes::size()>{});
        bytes pattern{bytes_ap};

        bytes bytes_v = bit_cast(v, eve::as<bytes>{});
        bytes_v       = byte_16_runtime_shuffle(bytes_v, pattern);
        v             = bit_cast(bytes_v, as(v));

        return v;
      }
      else if constexpr ( N() == 8 )
      {
        u_t const* pattern_p = pattern_8_elements_bytes_v<u_t>[num].data();
        auto     * bytes_p   = (std::uint8_t const*) (pattern_p);
        auto       bytes_ap  = eve::as_aligned(bytes_p, eve::fixed<bytes::size()>{});
        bytes pattern{bytes_ap};

        // Shuffle
        bytes bytes_v = bit_cast(v, eve::as<bytes>{});
        bytes_v       = byte_16_runtime_shuffle(bytes_v, pattern);
        v             = bit_cast(bytes_v, as(v));

        return v;
      }
    }
  }

  template <typename T, typename N>
  EVE_FORCEINLINE
  auto compress_using_masks_to_left_(EVE_SUPPORTS(cpu_), wide<T, N> v)
  {
    if constexpr ( !kumi::product_type<T> ) return eve::slide_left(v, eve::index<1>);
    else
    {
      return wide<T, N>{ kumi::map(compress_using_masks_to_left, v) };
    }
  }

  template <typename T, typename N, typename U>
  constexpr bool compress_using_masks_should_aggregate()
  {
         if constexpr ( max_scalar_size_v<T> * N() <= 16 && N() <= 8 ) return false;
    else if constexpr ( current_api == avx2              && N() == 4 ) return false;
    else return true;
  }

  template<relative_conditional_expr C, typename T, typename U, typename N>
  EVE_FORCEINLINE
  auto compress_using_masks_(EVE_SUPPORTS(cpu_),
                           C c,
                           wide<T, N> v,
                           logical<wide<U, N>> mask) noexcept
  {
    constexpr bool treat_like_aggregate = compress_using_masks_should_aggregate<T, N, U>();

    if constexpr ( C::is_complete && !C::is_inverted )
    {
      kumi::tuple cur{ v, (std::ptrdiff_t) 0 };
      return kumi::tuple<decltype(cur)> { cur };
    }
    // In all of these cases we should remove ignore
    else if constexpr ( (treat_like_aggregate || N() != 4) && !C::is_complete )
    {
      mask = mask && c.mask(as(mask));
      return compress_using_masks(ignore_none, v, mask);
    }
    else if constexpr ( treat_like_aggregate )
    {
      auto [l, h] = v.slice();
      auto [ml, mh] = mask.slice();

      auto lr = compress_using_masks(ignore_none, l, ml);
      auto hr = compress_using_masks(ignore_none, h, mh);

      return kumi::cat(lr, hr);
    }
    else if constexpr ( N() == 1 )
    {
      kumi::tuple cur{ v, (std::ptrdiff_t) mask.get(0) };
      return kumi::tuple<decltype(cur)> { cur };
    }
    else if constexpr ( N() == 2 )
    {
      auto to_left     = eve::slide_left( v, eve::index<1> );
      auto compressed  = eve::if_else[mask]( v, to_left );

      kumi::tuple cur{ compressed, eve::count_true(mask) };
      return kumi::tuple<decltype(cur)> { cur };
    }
    else if constexpr ( N() == 4 )
    {
      auto [num, count] = compress_store_swizzle_mask_num[c](mask);
      kumi::tuple cur { compress_using_masks_shuffle(v, num), count };
      return kumi::tuple<decltype(cur)> { cur };
    }
    else if constexpr ( N() == 8 )
    {
      // Reduce variations: in each pair from 4 to 3. 10 and 01 become the same.
      // Two last elements don't matter.
      v = eve::if_else[mask]( v, compress_using_masks_to_left( v ) );

      auto [num, count] = compress_store_swizzle_mask_num(mask);
      kumi::tuple cur { compress_using_masks_shuffle(v, num), count };
      return kumi::tuple<decltype(cur)> { cur };
    }
  }
}
