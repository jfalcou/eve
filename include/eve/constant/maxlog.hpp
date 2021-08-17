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
  EVE_MAKE_CALLABLE(maxlog_, maxlog);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto maxlog_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = detail::value_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x42b0c0a5U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x40862b7d369a5aa7ULL>();
    }
    //          0x40862e42fefa39efULL>(); // 709.43613930310391
  }
}
