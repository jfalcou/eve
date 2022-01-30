//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto manhattan_(EVE_SUPPORTS(cpu_)
                            , pedantic_type const &
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic(manhattan), a, b);
  }
  template<floating_value T>
  EVE_FORCEINLINE auto manhattan_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a
                             , T const &b
                             ) noexcept
  requires has_native_abi_v<T>
  {
    const auto infty = inf(eve::as(a));
    auto aa = eve::abs(a);
    auto infa = aa == infty;
    if constexpr(scalar_value<T>) { if (infa) return infty;}
    auto bb = eve::abs(b);
    auto infb = bb == infty;
    if constexpr(scalar_value<T>) { if (infb) return infty; }
    auto r =  eve::abs(a)+eve::abs(b);
    if constexpr(scalar_value<T>) { return r; }
    else { return if_else(infa || infb ,  infty, r); }
  }

  template<floating_value T, floating_value U, floating_value V>
  EVE_FORCEINLINE  auto manhattan_(EVE_SUPPORTS(cpu_)
                            , pedantic_type const &
                              , T const &a
                              , U const &b
                              , V const &c) noexcept
  requires compatible_values<T, U> &&  compatible_values<T, V>
  {
    return arithmetic_call(pedantic(manhattan), a, b, c);
  }

  template<floating_value T>
  EVE_FORCEINLINE auto manhattan_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a
                             , T const &b
                             , T const &c
                             ) noexcept
  requires has_native_abi_v<T>
  {
    const auto infty = inf(eve::as(a));
    auto aa = eve::abs(a);
    auto infa = aa == infty;
    if constexpr(scalar_value<T>) { if (infa) return infty;}
    auto bb = eve::abs(b);
    auto infb = bb == infty;
    if constexpr(scalar_value<T>) { if (infb) return infty; }
    auto cc = eve::abs(c);
    auto infc = cc == infty;
    if constexpr(scalar_value<T>) { if (infc) return infty; }
    auto r =  eve::abs(a)+eve::abs(b)+eve::abs(c);
    if constexpr(scalar_value<T>) { return r; }
    else { return if_else(infa || infb || infc,  infty, r); }
  }

}
