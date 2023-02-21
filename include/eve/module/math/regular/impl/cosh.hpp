//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/regular/exp.hpp>

namespace eve::detail
{

template<ordered_value T>
EVE_FORCEINLINE constexpr auto
cosh_(EVE_SUPPORTS(cpu_), T a0) noexcept
{
  //////////////////////////////////////////////////////////////////////////////
  // if x = abs(a0) according x < Threshold e =  exp(x) or exp(x/2) is
  // respectively computed
  // *  in the first case cosh (e+rec(e))/2
  // *  in the second     cosh is (e/2)*e (avoiding undue overflow)
  // Threshold is maxlog - Log_2
  //////////////////////////////////////////////////////////////////////////////
  if constexpr( scalar_value<T> )
  {
    if( is_eqz(a0) ) return one(eve::as(a0));
  }
  if constexpr( has_native_abi_v<T> )
  {
    T ovflimitmln2 = maxlog(as(a0))-log_2(as(a0));
//       Ieee_constant<underlying_type_t<T>, 0X42AF5DC0U, 0X408628B76E3A7B61LL>()); // 87.68310404,
//                                                               // 709.08956571282405469058276787854
    auto x = eve::abs(a0);
    if constexpr( scalar_value<T> )
    {
      if(is_not_finite(x)) return x;
      else if( x >= ovflimitmln2 )
      {
        auto w = exp(x * half(eve::as<T>()));
        auto t = half(eve::as<T>()) * w;
        t *= w;
        return t;
      }
      auto t = exp(x);
      return (x > 22) ? t * half(eve::as<T>()) : average(t, rec(t));
    }
    else
    {
      auto t    = exp(x);
      auto invt = if_else(x > 22, eve::zero, rec(t));
      auto c    = average(t, invt);
      auto test = x < ovflimitmln2;
      if( eve::all(test) ) return c;
      auto w = exp(x * half(eve::as<T>()));
      t      = half(eve::as<T>()) * w;
      t *= w;

      c = if_else(test, c, t);
      return c;
    }
  }
  else return apply_over(cosh, a0);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
cosh_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::cosh, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
cosh_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::cosh), t);
}
}
