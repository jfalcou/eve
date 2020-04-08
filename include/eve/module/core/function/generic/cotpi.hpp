//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_COTPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_COTPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/module/core/detail/generic/rem2.hpp>
#include <eve/module/core/detail/generic/trig_finalize.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/trigo_tags.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_)
                                       , restricted_type const &
                                       , T a0) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if (is_eqz(a0)) return bit_or(a0, Inf(as(a0)));
        auto x = abs(a0);
        if (is_not_less_equal(x, T(0.25))) return Nan<T>();
        return rec(tancot_eval(Pi<T>()*a0));
      }
      else
      {
        auto x  = eve::abs(a0);
        return if_else(is_eqz(a0), bit_or(a0, Inf(as(a0)))
                      , if_else(is_not_less_equal(x, T(0.25))
                               , eve::allbits_, rec(tancot_eval(Pi<T>()*a0))));
      }
    }
    else return apply_over(restricted_(cotpi), a0);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  // medium,  big,  small
  template<typename D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_)
                                       , D  const &
                                       , T a0) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if (is_eqz(a0)) return bit_or(a0, Inf(as(a0)));
        if (is_not_finite(a0)||is_flint(a0)) return Nan<T>();
      }
      auto x =  abs(a0);
      if constexpr(simd_value<T>)
      {
        x = if_else (is_not_finite(a0) || is_flint(x), eve::allbits_, x);
      }
       auto [fn, xr, dxr] =  rem2(x);
      return cot_finalize(a0*Pi<T>(), quadrant(fn), xr, dxr);
    }
    else return apply_over(D()(cotpi), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_)
                                       , T const &a0) noexcept
  {
    if constexpr(native<T>)
    {
      auto x =  abs(a0);
      if (all(eve::abs(x) <= T(0.25))) return restricted_(cotpi)(a0);
      else                             return big_(cotpi)(a0);
    }
    else                               return apply_over(cotpi, a0);
  }
}

#endif
