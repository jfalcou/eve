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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/roundings.hpp>

namespace eve::detail
{

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    if (integral_value<T>)
      return a % b;
    else
      return arithmetic_call(rem, a, b);
  }

 template<real_value T>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return toward_zero_(rem)(a, b);
    }
    else
      return apply_over(toward_zero_(rem), a, b);
  }

  template<real_value T, real_value U, decorator D>
  EVE_FORCEINLINE auto
  rem_(EVE_SUPPORTS(cpu_), D const &, T const &a, U const &b) noexcept requires compatible_values<T, U>
  {
    return arithmetic_call(D()(rem), a, b);
  }

  template<real_value T, decorator D>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_), D const& d, T const &a, T const &b) noexcept
  {
    return fnma(b, d(eve::div)(a,b), a);
  }

  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_), D const& , T const &a, T const &b) noexcept
  requires(is_one_of<D>(types<to_nearest_type, toward_zero_type> {}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto tmp =  fnma(b, D()(eve::div)(a,b), a);
      return if_else(is_eqz(tmp), copysign(tmp, a),  tmp);
    }
    else
      return apply_over(D()(rem), a, b);

  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<value T, real_value U, real_value V>
  EVE_FORCEINLINE auto rem_(EVE_SUPPORTS(cpu_), T const &cond, U const &t, V const &f) noexcept
  requires compatible_values<U, V>
  {
    using r_t = decltype(if_else(cond, f, t));
    if constexpr( scalar_value<T> )
    {
      return cond ? toward_zero_(rem)(t, f) : r_t(t);
    }
    else if constexpr( simd_value<T> )
    {
      return if_else(cond, toward_zero_(rem)(r_t(t), r_t(f)), r_t(t));
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
      return cond.value ? r_t(t) : toward_zero_(rem)(t, f);
    }
    else if constexpr( simd_value<T> )
    {
      return if_else(cond, r_t(t), toward_zero_(rem)(r_t(t), r_t(f)));
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
