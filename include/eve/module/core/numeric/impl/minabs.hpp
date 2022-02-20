//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/numeric/min.hpp>
#include <eve/platform.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto minabs_(EVE_SUPPORTS(cpu_), numeric_type const &
                              , T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(numeric(minabs), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto minabs_(EVE_SUPPORTS(cpu_), numeric_type const &
                              , T const &a, T const &b) noexcept
  {
    return eve::numeric(min)(eve::abs(a), eve::abs(b));
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  auto minabs_(EVE_SUPPORTS(cpu_), numeric_type const &, T0 a0, T1 a1, Ts... args)
  {
    using r_t = common_compatible_t<T0,T1,Ts...>;
    r_t that(numeric(minabs)(r_t(a0),r_t(a1)));
    ((that = numeric(minabs)(that,r_t(args))),...);
    return that;
  }
}
