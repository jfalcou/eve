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

#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(combine_, combine);
}

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE auto combine_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  {
    return as_wide_t<T, typename cardinal_t<T>::combined_type>(a, b);
  }
}
