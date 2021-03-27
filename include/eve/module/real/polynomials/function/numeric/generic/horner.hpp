//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/numeric/fma.hpp>

namespace eve::detail
{

  template<value T0, value T1>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , numeric_type const &
                                        , T0 const &, T1 const &a) noexcept
      requires compatible_values<T0, T1>
  {
    using r_t = common_compatible_t<T0, T1>;
    return r_t(a);
  }

  template<value T0, value T1, value T2>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , numeric_type const &
                                        , T0 const &x, T1 const &a, T2 const &b) noexcept
      requires compatible_values<T0, T1> &&compatible_values<T1, T2>
  {
    using r_t = common_compatible_t<T0, T1, T2>;
    return numeric(fma)(r_t(x), a, b);
  }

  //================================================================================================
  //N parameters (((..(a*x+b)*x+c)*x + ..)..)
  //================================================================================================

  template<value T0,
           value T1,
           value T2,
           value ...Ts>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , numeric_type const &
                                        , T0 xx, T1 a, T2 b, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T1, T2, Ts...>;
    auto x =  r_t(xx);
    r_t that(numeric(fma)(x, a, b));
    auto next = [x](auto that, auto arg){
      return numeric(fma)(x, that, arg);
    };
    ((that = next(that, args)),...);
    return that;
  }
}
