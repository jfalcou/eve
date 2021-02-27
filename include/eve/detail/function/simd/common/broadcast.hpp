//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<simd_value Wide>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(cpu_), Wide v, auto Index) noexcept
  {
    return Wide{ v.get(Index) };
  }

  template<simd_value Wide, std::ptrdiff_t N>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(cpu_), Wide v, auto Index, fixed<N>) noexcept
  {
    using  that_t = as_wide_t<Wide,fixed<N>>;
    return that_t{ v.get(Index) };
  }
}
