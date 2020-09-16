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
#include <eve/as.hpp>
#include <cstring>

namespace eve
{
  EVE_MAKE_CALLABLE(bit_cast_, bit_cast);
}

namespace eve::detail
{
  template<typename T, typename Target>
  EVE_FORCEINLINE auto bit_cast_(EVE_SUPPORTS(cpu_), T const &a, as_<Target> const &) noexcept
  requires (sizeof(T) == sizeof(Target))
  {
    if constexpr(std::is_same_v<T, Target>)
    {
      return a;
    }
    else
    {
      [[maybe_unused]] Target that;
      std::memcpy((char*)&that, (char*)&a, sizeof(a));
      return that;
    }
  }
}
