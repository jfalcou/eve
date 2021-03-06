//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
  EVE_MAKE_CALLABLE(oneotwoeps_, oneotwoeps);

  namespace detail
  {
    template<real_value T>
    EVE_FORCEINLINE constexpr auto oneotwoeps_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0X4A800000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X4320000000000000ULL>();
      else return T(1);
    }
  }
}
