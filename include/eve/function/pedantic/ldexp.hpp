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

#include <eve/function/ldexp.hpp>
#include <eve/function/pedantic.hpp>

namespace eve
{
  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::ldexp_), pedantic_type const&, T const&,  [[maybe_unused]] U const& b)
    {
      if constexpr(std::is_floating_point_v<value_type_t<U>>)
        EVE_ASSERT(all(is_flint(b)), "ldexp argument 2 is floating but not a flint");
    }
  }
}

#include <eve/module/core/function/pedantic/generic/ldexp.hpp>
