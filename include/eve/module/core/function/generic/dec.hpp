//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_DEC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_DEC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<real_value T>
  EVE_FORCEINLINE constexpr T dec_(EVE_SUPPORTS(cpu_)
                                  , T const &v) noexcept
  {
    if constexpr(native<T>)  return v - One(as(v));
    else                     return apply_over(dec, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated case
  template<real_value T>
  EVE_FORCEINLINE constexpr T dec_(EVE_SUPPORTS(cpu_)
                                  , saturated_type const &
                                  , T const &a) noexcept
  {
    if constexpr(native<T>)
    {
           if constexpr(integral_value<T>) return dec[ a != Valmin(as(a)) ](a);
      else if constexpr(floating_value<T>) return dec(a);
    }
    else return apply_over(dec, a);
  }

  // -----------------------------------------------------------------------------------------------
  // Basic masked
  template<real_value T, value COND>
  EVE_FORCEINLINE constexpr T dec_(EVE_SUPPORTS(cpu_)
                                  , COND const & cond
                                  , T const &v) noexcept
  {
    if constexpr(native<T>)
    {
           if constexpr(scalar_value<COND>) return cond ? dec(v) : v;
      else if constexpr(integral_value<T>)  return v + (bit_mask(bit_cast(cond,as(v))));
      else if constexpr(floating_value<T>)  return if_else(cond, dec(v), v);
    }
    else                                    return apply_over(dec, cond, v);
  }

  // -----------------------------------------------------------------------------------------------
  // saturated masked
  template<real_value T, value COND>
  EVE_FORCEINLINE constexpr T dec_(EVE_SUPPORTS(cpu_)
                                  , COND const & cond
                                  , saturated_type const &
                                  , T const &v) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(floating_value<T>) return if_else(cond, dec(v), v);
      else
      {
        auto tst = is_not_equal(Valmin(as(v)), v);
             if constexpr(scalar_value<COND>)  return cond ? dec[tst](v) : v;
        else if constexpr(integral_value<T>)   return dec[ tst && cond ](v);
      }
    }
    else                                       return apply_over(saturated_(dec), cond, v);
  }
}

#endif
