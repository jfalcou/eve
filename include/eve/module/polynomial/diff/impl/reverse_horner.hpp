//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/polynomial/regular/reverse_horner.hpp>
#include <eve/module/polynomial/pedantic/reverse_horner.hpp>

namespace eve::detail
{

  template<value T0, value T1>
  EVE_FORCEINLINE constexpr auto reverse_horner_(EVE_SUPPORTS(cpu_)
                                                , diff_type<1> const &
                                                , T0 const &, T1 const &) noexcept
  requires compatible_values<T0, T1>
  {
    using r_t = common_compatible_t<T0, T1>;
    return zero(as<r_t>());
  }

  template<value T0, value T1, value T2>
  EVE_FORCEINLINE constexpr auto reverse_horner_(EVE_SUPPORTS(cpu_)
                                                , diff_type<1> const &
                                                , T0 const & b, T1 const &, T2 const &) noexcept
  requires compatible_values<T0, T1> &&compatible_values<T1, T2>
  {
    using r_t = common_compatible_t<T0, T1, T2>;
    return r_t(b);
  }

  //================================================================================================
  //N parameters (((..(a*x+b)*x+c)*x + ..)..)
  //================================================================================================

  template<value T0,
           value T1,
           value T2,
           value ...Ts>
           EVE_FORCEINLINE constexpr auto reverse_horner_(EVE_SUPPORTS(cpu_)
                                                         , diff_type<1> const &
                                                         , T0 x, T1 a, T2 b, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T1, T2, Ts...>;
    auto preverse_horner = pedantic(reverse_horner);
    auto n = sizeof...(args)+1;
    r_t that(preverse_horner(n*x, a, b));
    auto next = [&x, &n,  &preverse_horner](auto that, auto arg){
      return preverse_horner(--n*x, that, arg);
    };
    ((that = next(that, args)),...);
    return that;
  }
}
