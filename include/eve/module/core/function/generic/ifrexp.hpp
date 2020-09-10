//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Jean-Thierry LAPRESTE
   Copyright 2020 Joel FALCOU

   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/add.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_notand.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/logical_notand.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/raw.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/maxexponentm1.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/expobits_mask.hpp>
#include <eve/constant/twotonmb.hpp>
#include <tuple>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , raw_type const &
                                        , T a0) noexcept

  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      auto r1   = bit_and(Expobits_mask<T>(), a0);
      auto x    = bit_notand(Expobits_mask<T>(), a0);
      return  std::make_tuple( bit_or(half(eve::as<T>()), x), bit_shr(r1,nbmantissabits(eve::as<elt_t>())) - maxexponentm1(eve::as<elt_t>()));
    }
    else  return apply_over2(raw_(ifrexp), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , T a0) noexcept

  {
    if constexpr(has_native_abi_v<T>)
    {
      auto [m, e] =  raw_(ifrexp)(a0);
      auto a0eqz = is_eqz(a0);
      if constexpr(scalar_value<T>)
      {
        using i_t = as_integer_t<T>;
        if (a0eqz) return std::make_tuple(T(0),i_t(0));
      }
      return std::make_tuple(if_else(a0eqz, eve::zero_, m)
                            , if_else(a0eqz, eve::zero_, e));
    }
    else  return apply_over2(ifrexp, a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , pedantic_type const &
                                        , T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
       using i_t = as_integer_t<T, signed>;
      if constexpr(simd_value<T>)
      {
         using elt_t =  element_type_t<T>;
        i_t t(0);
        if constexpr(eve::platform::supports_denormals)
        {
          auto test = is_denormal(a0);
          t = if_else(test,nbmantissabits(eve::as<T>()), eve::zero_);
          a0 = if_else(test, Twotonmb<T>()*a0, a0);
        }
        auto e = bit_and(Expobits_mask<T>(), a0); //extract exp.
        auto x  = bit_notand(Expobits_mask<T>(), a0);
        e = bit_shr(e,nbmantissabits(eve::as<elt_t>())) - maxexponentm1(eve::as<elt_t>());
        auto r0 = bit_or(half(eve::as<T>()), x);
        auto test0 = is_nez(a0);
        auto test1 = is_greater(e,limitexponent(eve::as<T>()));
        auto ee = if_else(logical_notand(test1, test0), e, eve::zero_);

        if constexpr(eve::platform::supports_denormals)
        {
          ee -= t ;
        }
        return std::make_tuple( if_else(test0, add[test1](r0,a0), eve::zero_), ee);
      }
      else  if constexpr(scalar_value<T>)
      {
        if (a0 == 0 || is_not_finite(a0))
        {
          return std::make_tuple(a0, i_t(0));
        }
        else if constexpr(scalar_value<T>)
        {
          auto const nmb  = nbmantissabits(eve::as<T>());
          i_t e    = bit_and(Expobits_mask<T>(), a0);  // extract exp.
          if constexpr(eve::platform::supports_denormals)
          {
            i_t t = i_t(0);
            if(is_eqz(e)) // denormal
            {
              a0 *= Twotonmb<T>();
              e  = bit_and(Expobits_mask<T>(), a0);  // extract exp. again
              t   = nmb;
            }
            T x  = bit_andnot(a0, Expobits_mask<T>());        // clear exp. in a0
            e = bit_shr(e,nmb)- maxexponentm1(eve::as<T>());         // compute exp.
            if (e > limitexponent(eve::as<T>())) return std::make_tuple(a0, i_t(0));
            e -= t;
            return std::make_tuple(bit_or(x,half(eve::as<T>())), e);
          }
          else
          {
            T x  = bit_andnot(a0, Expobits_mask<T>());        // clear exp. in a0
            e = bit_shr(e,nmb)- maxexponentm1(eve::as<T>());         // compute exp.
            if (e > limitexponent(eve::as<T>())) return std::make_tuple(a0, i_t(0));
            return std::make_tuple(bit_or(x,half(eve::as<T>())), e);
          }
        }
      }
    }
    else  return apply_over2(pedantic_(ifrexp), a0);
  }


}
