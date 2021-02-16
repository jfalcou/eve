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
  template<simd_value Wide>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(cpu_), Wide v, auto Index) noexcept
  {
    return v[broadcast_n<Index,cardinal_v<Wide>>];
  }

  template<typename Wide, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(cpu_), logical<Wide> v, Pattern p) noexcept
  {
    constexpr auto sz = Pattern::size(cardinal_v<logical<Wide>>);
    using   that_t    = as_wide_t<logical<Wide>,fixed<sz>>;

    return that_t{ v.get(p(0,sz)) };
  }

  template<simd_value Wide, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(cpu_), Wide v, Pattern p) noexcept
  {
    constexpr auto sz = Pattern::size(cardinal_v<Wide>);
    using   that_t    = as_wide_t<Wide,fixed<sz>>;

    return that_t{ v.get(p(0,sz)) };
  }
}
