//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/is_not_less.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/mone.hpp>

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

  template<auto N, conditional_expr C, floating_value T, floating_value U>
  EVE_FORCEINLINE  auto fdim_(EVE_SUPPORTS(cpu_)
                            , C const &cond
                            , diff_type<N> const &
                            , T const &a
                            , U const &b) noexcept
  {
    return mask_op(  cond, eve::diff_nth<N>(eve::fdim), a, b);
  }
}
