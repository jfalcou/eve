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
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(is_nez_, is_nez);
}

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE constexpr auto is_nez_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return detail::to_logical(a);
  }
}
