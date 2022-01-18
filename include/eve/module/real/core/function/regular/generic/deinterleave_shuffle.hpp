//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/real/core/detail/basic_shuffle.hpp>
#include <eve/function/combine.hpp>
#include <eve/concept/abi.hpp>

namespace eve::detail
{
  template <typename T, typename N>
  EVE_FORCEINLINE
  auto deinterleave_shuffle_aggregation(wide<T, N> v0, wide<T, N> v1)
  {
    auto [a0b0,a1b1] = v0.slice();
    auto [a2b2,a3b3] = v1.slice();

    auto [a0a1,b0b1] = deinterleave_shuffle(a0b0,a1b1).slice();
    auto [a2a3,b2b3] = deinterleave_shuffle(a2b2,a3b3).slice();

    wide<T, N> l = eve::combine(a0a1, a2a3);
    wide<T, N> h = eve::combine(b0b1, b2b3);

    return eve::combine(l, h);
  }

  template <typename T, typename N>
  EVE_FORCEINLINE
  wide<T, N> deinterleave_shuffle_aggregation(wide<T, N> v)
  {
    auto [v0,v1] = v.slice();

    return deinterleave_shuffle_aggregation(v0, v1);
  }

  template <simd_value Wide>
  EVE_FORCEINLINE auto deinterleave_shuffle_(EVE_SUPPORTS(cpu_), Wide v) noexcept
  {
         if constexpr ( Wide::size() <= 2                   ) return v;
    else if constexpr( has_aggregated_abi_v<Wide>           )
    {
      auto [v0,v1] = v.slice();
      return deinterleave_shuffle(v0, v1);
    }
    else if constexpr( is_bundle_v<typename Wide::abi_type> ) return Wide(kumi::map(deinterleave_shuffle, v));
    else return basic_shuffle(v, deinterleave_shuffle_pattern<Wide::size()>);
  }

  template <simd_value Wide>
  EVE_FORCEINLINE auto deinterleave_shuffle_(EVE_SUPPORTS(cpu_), Wide v0, Wide v1) noexcept
  {
    using T = eve::element_type_t<Wide>;
    using N = eve::fixed<Wide::size()>;
    using res_t = as_wide_t<T, typename N::combined_type>;

         if constexpr ( res_t::size() <= expected_cardinal_v<T> ) return deinterleave_shuffle( eve::combine(v0, v1) );
    else if constexpr ( is_bundle_v<typename Wide::abi_type>    ) return res_t(kumi::map(deinterleave_shuffle, v0, v1));
    else if constexpr ( has_aggregated_abi_v<Wide>              )
    {
      auto [a0b0,a1b1] = v0.slice();
      auto [a2b2,a3b3] = v1.slice();

      auto [a0a1,b0b1] = deinterleave_shuffle(a0b0,a1b1).slice();
      auto [a2a3,b2b3] = deinterleave_shuffle(a2b2,a3b3).slice();

      wide<T, N> l = eve::combine(a0a1, a2a3);
      wide<T, N> h = eve::combine(b0b1, b2b3);

      return eve::combine(l, h);
    }
    else
    {
      return res_t {[&](int i, int size) {
        if ( i < size / 4) return v0.get(2 * i);
        i -= size / 4;
        if ( i < size / 4 ) return v1.get(2 * i);
        i -= size / 4;
        if (i < size / 4) return v0.get(2 * i + 1);
        i -= size / 4;
        return v1.get(2 * i + 1);
      }};
    }
  }
}
