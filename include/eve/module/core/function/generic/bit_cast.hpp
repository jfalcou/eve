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
#include <eve/detail/alias.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/as.hpp>
#include <cstring>

namespace eve::detail
{

  template<typename T, typename Target>
  EVE_FORCEINLINE auto bit_cast_(EVE_SUPPORTS(cpu_),
                                     T const &a,
                                     as_<Target> const &) noexcept
  requires (sizeof(T) == sizeof(Target))
  {
    if constexpr(std::is_same_v<T, Target>) return a;
    else
    {
      Target that;

      void const *src = reinterpret_cast<detail::alias_t<void const> *>(&a);
      void *      dst = reinterpret_cast<detail::alias_t<void> *>(&that);
      std::memcpy(dst, src, sizeof(a));

      return that;
    }
  }
}

