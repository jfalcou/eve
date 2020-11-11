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
#include <eve/traits/element_type.hpp>
#include <eve/patterns.hpp>

#include <cstddef>

namespace eve::detail
{
  // Match any pattern when everything has failed
  struct any_match
  {
    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...>, as_<In>, as_<Out>)  noexcept
    {
      return true;
    }
  };

  template<typename Target, typename Wide, std::ptrdiff_t... I>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(cpu_), any_match const&
                                  , as_<Target> , pattern_<I...> const&
                                  , Wide const& v
                                  )
  {
    using type  = element_type_t<Wide>;
    return Target( (I == -1 ? type{0} : v[I])...);
  }
}
