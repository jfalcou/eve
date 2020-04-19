//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SECPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SECPI_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/rec.hpp>
#include <eve/module/core/detail/generic/trig_finalize.hpp>
#include <eve/module/core/detail/generic/rem2.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/nan.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto secpi_(EVE_SUPPORTS(cpu_)
                                      , restricted_type const &
                                      , T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto x = abs(a0);
      auto test = is_not_less_equal(x, T(0.25));
      if constexpr(scalar_value<T>)
      {
        if (test) return Nan<T>();
      }
      else
      {
        a0 = if_else(test, eve::allbits_, a0);
      }

      a0 *= Pi<T>();
      auto x2 = sqr(a0);
      return rec(detail::cos_eval(x2));
    }
    else
    {
      return apply_over(restricted_(secpi), a0);
    }
  }

  template<floating_real_value T,  typename D>
  EVE_FORCEINLINE constexpr auto secpi_(EVE_SUPPORTS(cpu_)
                                      , D const &
                                      , T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      const T x =  abs(a0);
      if constexpr(scalar_value<T>)
      {
        if (is_not_finite(x))  return Nan<T>();
        if (x > Maxflint<T>()) return T(1);
      }

      auto [fn, xr, dxr] =  rem2(x);
      T z = cos_finalize(quadrant(fn), xr, dxr);
      if constexpr(scalar_value<T>)
      {
        return (z) ? rec(cos_finalize(quadrant(fn), xr, dxr)) : Nan<T>() ;
      }
      else
      {
        return if_else(is_nez(z) && is_finite(a0), rec(z), eve::allbits_);
      }
    }
    else
    {
      return apply_over(D()(secpi), a0);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto secpi_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return big_(secpi)(a0);
    }
    else
    {
      return apply_over(secpi, a0);
    }
  }


}

#endif
