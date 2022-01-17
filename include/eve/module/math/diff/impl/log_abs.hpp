//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/horizontal.hpp>
#include <eve/function/log_abs.hpp>
#include <eve/function/diff/log.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/factorial.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/derivative.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{
  template<floating_real_value T, unsigned_value N>
  EVE_FORCEINLINE constexpr T log_abs_(EVE_SUPPORTS(cpu_)
                                     , diff_type<1> const &
                                     , T x
                                     , N n) noexcept
  {
    return diff(log)(eve::abs(x), n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T log_abs_(EVE_SUPPORTS(cpu_)
                                     , diff_type<1> const &
                                     , T x) noexcept
  {
    return rec(x);
  }
}
