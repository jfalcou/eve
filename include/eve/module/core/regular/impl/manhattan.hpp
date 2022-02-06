//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  //================================================================================================
  //N parameters
  //================================================================================================
  template<real_value T0, real_value ...Ts>
  auto manhattan_(EVE_SUPPORTS(cpu_), pedantic_type const &, T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    r_t that(eve::abs(a0));
    auto inf_found = is_infinite(that);
    auto addabs = [&inf_found](auto that, auto next)->r_t{
      auto z = eve::abs(next);
      inf_found = inf_found || is_infinite(z);
      that+= z;
      return that;
    };
    ((that = addabs(that,args)),...);
    return if_else(inf_found, inf(as<r_t>()), that);
  }

  template<real_value T0, real_value ...Ts>
  common_compatible_t<T0,Ts...> manhattan_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    r_t that(eve::abs(a0));
    auto addabs = [](auto that, auto next)->r_t{
      that+= eve::abs(next);
      return that;
    };
    ((that = addabs(that,args)),...);
    return that;
  }
}
