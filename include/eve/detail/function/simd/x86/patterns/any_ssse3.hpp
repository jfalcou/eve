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

#include <eve/detail/implementation.hpp>
#include <eve/detail/swizzle.hpp>

namespace eve::detail
{
  //================================================================================================
  // Arbitrary SSSE3 pattern
  //================================================================================================
  struct ssse3_match
  {
    template<typename Wide, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...> const&, as_<Wide> const&)  noexcept
    {
      using t_t = element_type_t<Wide>;
      return (cardinal_v<Wide> <= expected_cardinal_t<t_t>::value) && (current_api >= ssse3);
    }
  };

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(sse2_), ssse3_match const&
                                  , as_<Target> , Pattern const& p, Wide const& v
                                  )
  {
    using st_t    = typename Target::storage_type;
    using bytes_t = typename Target::template rebind<std::uint8_t>;

    return Target ( (st_t)_mm_shuffle_epi8( (__m128i)(v.storage())
                                          , as_bytes<Wide>(p,as_<bytes_t>())
                                          )
                  );
  }
}
