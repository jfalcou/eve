//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_INC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_INC_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<real_value T>
  EVE_FORCEINLINE constexpr T inc_(EVE_SUPPORTS(cpu_)
                                  , T const &v) noexcept
  {
    if constexpr(native<T>)  return v + One(as(v));
    else                     return apply_over(inc, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated case
  template<real_value T>
  EVE_FORCEINLINE constexpr T inc_(EVE_SUPPORTS(cpu_)
                                  , saturated_type const &
                                  , T const &a) noexcept
  {
    if constexpr(native<T>)
    {
           if constexpr(integral_value<T>) return inc[ a != Valmax(as(a)) ](a);
      else if constexpr(floating_value<T>) return inc(a);
    }
    else return apply_over(inc, a);
  }

  // -----------------------------------------------------------------------------------------------
  // Basic masked
  template<real_value T, value COND>
  EVE_FORCEINLINE constexpr T inc_(EVE_SUPPORTS(cpu_)
                                  , COND const & cond
                                  , T const &v) noexcept
  {
    if constexpr(native<T>)
    {
           if constexpr(scalar_value<COND>) return cond ? inc(v) : v;
      else if constexpr(integral_value<T>)  return v - (bit_mask(bit_cast(cond,as(v))));
      else if constexpr(floating_value<T>)  return if_else(cond, inc(v), v);
    }
    else                                    return apply_over(inc, cond, v);
  }

  // -----------------------------------------------------------------------------------------------
  // saturated masked
  template<real_value T, value COND>
  EVE_FORCEINLINE constexpr T inc_(EVE_SUPPORTS(cpu_)
                                  , COND const & cond
                                  , saturated_type const &
                                  , T const &v) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(floating_value<T>) return if_else(cond, inc(v), v);
      else
      {
        auto tst = is_not_equal(Valmax(as(v)), v);
             if constexpr(scalar_value<COND>)  return cond ? inc[tst](v) : v;
        else if constexpr(integral_value<T>)   return inc[ tst && cond ](v);
      }
    }
    else                                       return apply_over(saturated_(inc), cond, v);
  }
}

#endif
