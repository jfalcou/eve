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
#include <eve/traits/as_wide.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Arbitrary SSSE3 pattern
  //------------------------------------------------------------------------------------------------
  struct any_ssse3
  {
    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const&, as_<Wide> const&)  noexcept
    {
      using t_t = element_type_t<Wide>;
      return (cardinal_v<Wide> <= expected_cardinal_t<t_t>::value) && (current_api >= ssse3);
    }
  };

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(ssse3_), any_ssse3 const&
                                  , Pattern const& p, Wide const& v
                                  )
  {
    using that_t  = as_wide_t<Wide,fixed<Pattern::size(cardinal_v<Wide>)>>;
    using st_t    = typename that_t::storage_type;
    using bytes_t = typename that_t::template rebind<std::uint8_t>;

    return that_t ( (st_t)_mm_shuffle_epi8( (__m128i)(v.storage())
                                          , as_bytes<Wide>(p,as_<bytes_t>())
                                          )
                  );
  }
}
