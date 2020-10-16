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

#include <eve/detail/function/patterns/slide_left.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/swizzle.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), slide_left const&
                                  , as_<Target> , [[maybe_unused]] Pattern const& p, Wide const& v
                                  )
  {
    constexpr auto c   = cardinal_v<Wide>;
    constexpr auto sft = Pattern{}(0,c);
    constexpr auto s   = sizeof(element_type_t<Wide>) * sft;

    return Target( (typename Wide::storage_type)_mm_srli_si128((__m128i)(v.storage()),s) );
  }
}
