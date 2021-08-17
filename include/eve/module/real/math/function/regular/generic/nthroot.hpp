//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/nan.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/add.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/none.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/sign.hpp>

#include <concepts>
#include <type_traits>

namespace eve::detail
{
  //////////////////////////////////////////////////////////////////
  // raw
  template<floating_real_value T, integral_scalar_value I>
  EVE_FORCEINLINE auto nthroot_(EVE_SUPPORTS(cpu_), raw_type const &
                               , T x, I n) noexcept
  {
    return raw(nthroot)(x, T(n));
  }

  template<floating_real_simd_value T, integral_simd_value I>
  EVE_FORCEINLINE auto nthroot_(EVE_SUPPORTS(cpu_), raw_type const &
                               , T x, I n) noexcept
  requires (cardinal_v<T> == cardinal_v<I>)
  {
    using elt_t =  element_type_t<T>;
    return raw(nthroot)(x, convert(n, as<elt_t>()));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto nthroot_(EVE_SUPPORTS(cpu_), raw_type const &
                               , T x, T n) noexcept
  {
    if constexpr( has_native_abi_v<T>)
    {
      auto r = pow(abs(x), rec(n));
      auto islezx = is_lez(x);
      if (none(islezx)) return r;
      else return if_else(is_eqz(x)
                         , if_else(is_ltz(n), inf(as(x)), zero)
                         , if_else(islezx && !is_odd(n), allbits, r*sign(x))
                         );
    }
    else
      return apply_over(raw(nthroot), x, n);
  }

  //////////////////////////////////////////////////////////////////
  // regular
  template<floating_real_value T, integral_scalar_value I>
  EVE_FORCEINLINE auto nthroot_(EVE_SUPPORTS(cpu_)
                               , T x, I n) noexcept
  {
    return nthroot(x, T(n));
  }

  template<floating_real_simd_value T, integral_simd_value I>
  EVE_FORCEINLINE auto nthroot_(EVE_SUPPORTS(cpu_)
                               , T x, I n) noexcept
  requires (cardinal_v<T> == cardinal_v<I>)
  {
    using elt_t =  element_type_t<T>;
    return nthroot(x, convert(n, as<elt_t>()));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto nthroot_(EVE_SUPPORTS(cpu_)
                               , T x, T n) noexcept
  {
    auto an =  abs(n);
    auto ax = eve::abs(x);
    auto y = raw(nthroot)(ax, an);
    auto p = pow(y, an);
    auto yinc = -((p - ax)/(an*p))*y;
    y = add[is_nez(y)&&is_finite(x)](y, yinc);
    y = if_else(is_negative(x) && is_even(an), allbits, y*sign(x));
    return if_else (is_ltz(n), rec(y), y);
  }
}
