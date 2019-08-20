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
  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), slide_left const&
                                  , Pattern const&, Wide const& v
                                  )
  {
    constexpr auto c  = cardinal_v<Wide>;
    constexpr auto sz = Pattern::size(c);
    constexpr auto s  = sizeof(element_type_t<Wide>) * (sz-1-slide_left::find_slide(Pattern(),sz));
    using st_t        = typename Wide::storage_type;
    using that_t      = as_wide_t<Wide,fixed<sz>>;

    return that_t( (st_t)_mm_srli_si128((__m128i)(v.storage()),s) );
  }
}
