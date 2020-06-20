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

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/bit_shl.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/maxexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE T ldexp_(EVE_SUPPORTS(cpu_)
                               , T const &a
                               , U const &b) noexcept
  {
    if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
    {
      using elt_t = element_type_t<T>;
      if constexpr(integral_value<U>)
      {
        auto ik =  b+Maxexponent<elt_t>();
        ik = bit_shl(ik, Nbmantissabits<elt_t>());
        if constexpr(scalar_value<decltype(ik)>)
          return a*bit_cast(ik, as<elt_t>());
        else
          return a*bit_cast(ik, as<T>());

      }
      else if constexpr(floating_value<U>)
      {
        return ldexp(a, toint_<T>(trunc)(b));
      }
    }
    else  return apply_over(ldexp, a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // pedantic case
  template<real_value T, real_value U>
  EVE_FORCEINLINE T ldexp_(EVE_SUPPORTS(cpu_)
                               , pedantic_type const &
                               , T const &a
                               , U const &b) noexcept
  {
    if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
    {
      using elt_t = element_type_t<T>;
      if constexpr(integral_value<U>)
      {
        auto e = toint_<T>(b);
        auto f = One<T>();
        if constexpr( eve::platform::supports_denormals)
        {
          auto denormal =  is_less(e, Minexponent<elt_t>());
          e = sub[denormal]( e, Minexponent<elt_t>());
          f = if_else(denormal, Smallestposval<elt_t>(), eve::one_);
        }
        auto test = is_equal(e, Limitexponent<elt_t>());
        f = inc[test](f);
        e = dec[test](e);
        e += Maxexponent<elt_t>();
        e = bit_shl(e, Nbmantissabits<elt_t>());
        if constexpr(scalar_value<decltype(e)>)
          return a*bit_cast(e, as(elt_t()))*f;
        else
          return a*bit_cast(e, as(T()))*f;
      }
      else if constexpr(floating_value<U>)
      {
        return pedantic_(ldexp)(a, s_toint_<T>(trunc(b)));
      }
    }
    else  return apply_over(ldexp, a, b);
  }


}
