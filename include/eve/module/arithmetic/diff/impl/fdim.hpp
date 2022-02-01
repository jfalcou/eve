//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr auto fdim_(EVE_SUPPORTS(cpu_)
                                    , diff_type<1> const &
                                    , T x
                                    , U y) noexcept
  requires compatible_values<T, U>
  {
    using r_t = common_compatible_t<T,U>;
    return if_else(is_not_less(x, y), one(as<r_t>()), zero);
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE constexpr auto fdim_(EVE_SUPPORTS(cpu_)
                                    , diff_type<2> const &
                                    , T x
                                    , U y) noexcept
  requires compatible_values<T, U>
  {
    using r_t = common_compatible_t<T,U>;
    return if_else(is_not_less(x, y), mone(as<r_t>()), zero);
  }
}
