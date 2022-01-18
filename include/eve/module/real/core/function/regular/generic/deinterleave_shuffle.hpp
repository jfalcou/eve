//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/real/core/detail/basic_shuffle.hpp>

namespace eve::detail
{
  template <simd_value Wide>
  EVE_FORCEINLINE auto deinterleave_shuffle_(EVE_SUPPORTS(cpu_), Wide v) noexcept
  {
         if constexpr ( Wide::size() <= 2 ) return v;
    else if constexpr( has_aggregated_abi_v<Wide> )
    {
      auto[l,h] = v.slice();
      return deinterleave_shuffle(l, h);
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

         if constexpr ( native_simd_for_abi<res_t>           ) return deinterleave_shuffle( res_t{v0, v1} );
    else if constexpr ( is_bundle_v<typename Wide::abi_type> ) return res_t(kumi::map(deinterleave_shuffle, v0, v1));
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
