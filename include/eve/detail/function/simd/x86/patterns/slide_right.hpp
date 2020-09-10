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

#include <eve/detail/function/patterns/slide_right.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/swizzle.hpp>

namespace eve::detail
{
  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), slide_right const&
                                  , as_<Target> , Pattern const&, Wide const& v
                                  )
  {
    constexpr auto s  = sizeof(element_type_t<Wide>) * slide_right::find_slide(Pattern());
    return Target( (typename Wide::storage_type)_mm_slli_si128((__m128i)(v.storage()),s) );
  }
}
