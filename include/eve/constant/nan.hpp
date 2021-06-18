//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(nan_, nan);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto nan_(EVE_SUPPORTS(cpu_), as<T> const& tgt) noexcept
    {
      return allbits(tgt);
    }
  }
}
