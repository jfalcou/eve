//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/patterns.hpp>

#include <cstddef>

namespace eve::detail
{
  // Match any pattern when everything has failed
  struct any_pattern
  {
    template<typename F, int Size, typename Wide>
    static constexpr auto check(swizzler_t<F,Size> const&, as_<Wide> const&)  noexcept
    {
      return true;
    }
  };

  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(cpu_), any_pattern const&
                                  , Pattern const& p, Wide const& v
                                  )
  {
    constexpr auto sz = Pattern::size(cardinal_v<Wide>);
    using type        = element_type_t<Wide>;
    using that_t      = as_wide_t<Wide,fixed<sz>>;

    auto impl = [&](auto... I) { return that_t( (p(I,sz) == -1 ? type{0} : v[p(I,sz)])...); };
    return apply<sz>(impl);
  }
}
