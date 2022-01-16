//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/derivative.hpp
#include <eve/module/arithmetic.hpp>

namespace eve::detail
{

  template<value T0, value T1>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , diff_type<1> const &
                                        , T0 const &, T1 const &) noexcept
  requires compatible_values<T0, T1>
  {
    using r_t = common_compatible_t<T0, T1>;
    return zero(as<r_t>());
  }

  template<value T0, value T1, value T2>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , diff_type<1> const &
                                        , T0 const &, T1 const &  b, T2  const &) noexcept
  requires compatible_values<T0, T1> &&compatible_values<T1, T2>
  {
    using r_t = common_compatible_t<T0, T1, T2>;
    return r_t(b);
  }

  //================================================================================================
  //N parameters (((..((n-1)*a*x+(n-2)*b)*x+c*(n-3))*x + ..)..)
  //================================================================================================

  template<value T0,
           value T1,
           value T2,
           value ...Ts>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , diff_type<1> const &
                                        , T0 x, T1 a, T2 b, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T1, T2, Ts...>;
    auto n = sizeof...(args)+1;
    r_t that(fma(n*x, a, (n-1)*b));
    --n;
    auto next = [x, &n](auto that, auto arg){
      return fma(x, that, --n*arg);
    };
    ((that = next(that, args)),...);
    return that;
  }
}
