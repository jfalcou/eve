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
#include <eve/patterns.hpp>

#include <cstddef>

namespace eve::detail
{
  //==================================================================================================
  // Match any pattern of the form [-1 -1 ... -1 -1]
  //==================================================================================================
  struct zero_match
  {
    template<typename In, typename Out, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...>, as_<In>, as_<Out>)  noexcept
    {
      return ((I == -1) && ...);
    }
  };

  template<typename Target, typename Wide, std::ptrdiff_t... I>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(cpu_), zero_match const&
                                  , as_<Target> , pattern_<I...> const&
                                  , Wide const&
                                  )
  {
    return Target(0);
  }
}
