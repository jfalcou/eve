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
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(minlogdenormal_, minlogdenormal);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto minlogdenormal_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0xc2cff1b5U>(); // -103.972084
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0xc0874910d52d3053ULL>();//-745.1332191019413358
    }
  }
}
