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
  //TODO: RENOMMAGE EN  Mantissanentmask
  EVE_MAKE_CALLABLE(mantissabits_mask_, mantissabits_mask_);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto mantissabits_mask_(EVE_SUPPORTS(cpu_), as_<T> const &) noexcept
    {
      using t_t = detail::value_type_t<T>;
      using i_t = detail::as_integer_t<t_t>;

      if constexpr(std::is_same_v<t_t, float>) return i_t(0x007FFFFFU);
      else if constexpr(std::is_same_v<t_t, double >) return i_t(0x000FFFFFFFFFFFFFULL);
    }
  }
}
