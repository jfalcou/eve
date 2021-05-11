//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/function/add.hpp>
#include <eve/function/all.hpp>
#include <eve/function/any.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/constant/one.hpp>
#include <utility>

namespace eve::detail
{

  template<integral_scalar_value I, floating_value T>
  EVE_FORCEINLINE auto laguerre_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
  {
    auto p0 = one(as(x));
    if(is_eqz(n)) return p0;
    auto p1 = oneminus(x);
    auto vc = one(as(x));
    auto c = one(as(n));
    while(c < n)
    {
      auto p = p0;
      p0 = p1;
      auto vcp1 = inc(vc);
      p1 = fms(vc + vcp1 - x, p0, vc * p) /vcp1;
      vc = vcp1;
      ++c;
    }
    return p1;
  }

  template<integral_simd_value I, floating_scalar_value T>
  EVE_FORCEINLINE auto laguerre_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
  {
    using f_t = as_wide_t<T, cardinal_t<I>>;
    return laguerre(nn, f_t(x));
  }

  template<integral_simd_value I, floating_simd_value T>
  EVE_FORCEINLINE auto laguerre_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
  //  requires index_compatible_values<I, T>
  {
   if (has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      auto p0 = one(as(x));
      auto iseqzn = is_eqz(nn);
      if(eve::all(iseqzn)) return p0;

      auto p1 = oneminus(x);
      auto n =  convert(nn, as<elt_t>());
      auto c = one(as(n));
      auto test = c < n;
      while(eve::any(test))
      {
        auto p = p0;
        p0 = p1;
        auto cp1 = inc(c);
        p1 = if_else(test, fms(c + cp1 - x, p0, c * p) /cp1, p1);
        c = cp1;
        test = c < n;
      }
      return  if_else(iseqzn,  one, p1);
    }
    else
      return apply_over(laguerre, nn, x);
  }
}
