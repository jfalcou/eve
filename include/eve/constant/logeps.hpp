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
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(logeps_, logeps);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto logeps_(EVE_SUPPORTS(cpu_), as_<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;

         if constexpr(std::is_same_v<t_t, float>)  return Constant<T,  0XC17F1402U>();
    else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0XC04205966F2B4F12ULL>();
    }
  }
}
