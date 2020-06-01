//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/roundings.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return fnma(b, toward_zero_(div)(a,b), a);
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_)
                            , pedantic_type const&,T const &a, U const &b
                            ) noexcept requires compatible_values<T, U>
  {
    return if_else(is_nez(b), rem(a,b), a);
  }

  template<real_value T, real_value U, decorator D>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_), D const& d, T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return fnma(b, d(eve::div)(a,b), a);
  }

  template<real_value T, real_value U, decorator D>
  EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_), pedantic_type const&, D const& d
                            , T const &a, U const &b
                            ) noexcept
  requires compatible_values<T, U>
  {
    return if_else(is_nez(b), d(rem)(a,b), a);
  }

  template<real_value T, real_value U, decorator D>
  EVE_FORCEINLINE auto rem_ ( EVE_SUPPORTS(cpu_), D const& d, pedantic_type const&
                            , T const &a, U const &b
                            ) noexcept
  requires compatible_values<T, U>
  {
    return if_else(is_nez(b), d(rem)(a,b), a);
  }
}

