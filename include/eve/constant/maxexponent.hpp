//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_integer.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(maxexponent_, maxexponent);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto maxexponent_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;
      using i_t = as_integer_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return i_t(127);
      else if constexpr(std::is_same_v<t_t, double >) return i_t(1023);
    }
  }
}
