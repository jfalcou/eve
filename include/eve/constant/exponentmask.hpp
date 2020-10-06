//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(exponentmask_, exponentmask);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto exponentmask_(EVE_SUPPORTS(cpu_), as_<T> const &) noexcept
    {
      using t_t = detail::value_type_t<T>;
      using i_t = detail::as_integer_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return i_t(0x7f800000);
      else if constexpr(std::is_same_v<t_t, double >) return i_t(0x7ff0000000000000LL);
    }
  }
}
