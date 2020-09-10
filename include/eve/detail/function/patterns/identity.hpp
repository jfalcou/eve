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
#include <eve/detail/swizzle.hpp>
#include <eve/patterns.hpp>

#include <cstddef>

namespace eve::detail
{
  // Match any pattern of the form [0 1 2 ... N-1]
  struct identity_match
  {
    template<typename Wide, std::ptrdiff_t... I>
    static constexpr auto check(pattern_<I...> const&, as_<Wide> const&)  noexcept
    {
      return  []<std::ptrdiff_t... V>( std::integer_sequence<std::ptrdiff_t,V...>)
              {
                return ((I == V) && ... );
              }( std::make_integer_sequence<std::ptrdiff_t,sizeof...(I)>{} );
    }
  };

  template<typename Target, typename Wide, std::ptrdiff_t... I>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(cpu_), identity_match const&
                                  , as_<Target> , pattern_<I...> const& p
                                  , Wide const& v
                                  )
  {
    constexpr auto sz = sizeof...(I);

    if constexpr(sz >= cardinal_v<Wide>)
    {
      return process_zeros(Target(v.storage()),p);
    }
    else if constexpr(cardinal_v<Wide>/sz == 2)
    {
      return process_zeros(Target(v.slice(lower_).storage()),p);
    }
    else
    {
      return do_swizzle(EVE_RETARGET(cpu_), identity_match{}, as_<Target>{}, p, v.slice(lower_));
    }
  }
}
