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

  //================================================================================================
  // Masked case
  //================================================================================================
  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_), T const &cond, U const &t, V const &f) noexcept
  //      requires compatible_values<U, V>
  {
    using r_t = decltype(rem(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond ? rem(t, f) : r_t(t);
    }
    else if constexpr( simd_value<T> )
    {
      return if_else(cond, rem(r_t(t), r_t(f)), r_t(t));
    }
  }

  template<value T, real_value U, real_value V, decorator D>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), T const &cond, D const &, U const &t, V const &f) noexcept
  requires compatible_values<U, V>
  {
    using r_t = decltype(D()(rem)(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond ? D()(rem)(t, f) : r_t(t);
    }
    else if constexpr( simd_value<T> )
    {
      return if_else(cond, D()(rem)(r_t(t), r_t(f)), r_t(t));
    }
  }

  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), not_t<T> const &cond, U const &t, V const &f) noexcept
  requires compatible_values<U, V>
  {
    using r_t = decltype(rem(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond.value ? r_t(t) : rem(t, f);
    }
    else if constexpr( simd_value<T> )
    {
      return if_else(cond, r_t(t), rem(r_t(t), r_t(f)));
    }
  }

  template<value T, real_value U, real_value V, decorator D>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_),
                            not_t<T> const &cond,
                            D const &,
                            U const &t,
                            V const &f) noexcept requires compatible_values<U, V>
  {
    using r_t = decltype(rem(t, f));
    if constexpr( scalar_value<T> )
    {
      return cond.value ? r_t(t) : D()(rem)(t, f);
    }
    else if constexpr( simd_value<T> )
    {
      return if_else(cond, r_t(t), D()(rem)(r_t(t), r_t(f)));
    }
  }
}
