//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/pattern.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<simd_value Wide> EVE_FORCEINLINE auto gather_low_(EVE_SUPPORTS(cpu_), Wide v) noexcept
  {
    // Well, we dunno how to do this, so we just reshuffle
    return v[gather_low_n<cardinal_v<Wide>>];
  }

  template<typename Wide, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto gather_low_( EVE_SUPPORTS(cpu_)
                                  , logical<Wide> const& v, Pattern p
                                  ) noexcept
  {
    constexpr auto sz = Pattern::size(cardinal_v<logical<Wide>>);
    using   that_t    = as_wide_t<logical<Wide>,fixed<sz>>;

    return bit_cast( v.mask()[p], as<that_t>() );
  }

  template<simd_value Wide, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto gather_low_(EVE_SUPPORTS(cpu_), Wide v, Pattern p) noexcept
  {
    constexpr auto sz = Pattern::size(cardinal_v<Wide>);
    using   that_t    = as_wide_t<Wide,fixed<sz>>;

    if constexpr( has_aggregated_abi_v<that_t> )  return aggregate_swizzle(v,p);
    else                                          return basic_swizzle(v,p);
  }
}
