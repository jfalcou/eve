//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ONEMINUS_HPP_ONEMINUSLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ONEMINUS_HPP_ONEMINUSLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/saturated.hpp>

#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Decorated
  template<real_value T, decorator D>
  EVE_FORCEINLINE constexpr T oneminus_(EVE_SUPPORTS(cpu_), D const &, T const &v) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      if constexpr( std::is_same_v<D, regular_type> || std::is_floating_point_v<elt_t> )
      {
        return One<T>() - v;
      }
      else if constexpr( std::is_same_v<D, saturated_type> )
      {
        if constexpr( std::is_unsigned_v<elt_t> )
        {
          return binarize(is_eqz(v));
        }
        if constexpr( scalar_value<T> )
        {
          return (v <= Valmin(as(v)) + 2) ? Valmax(as(v)) : oneminus(v);
        }
        else if constexpr( simd_value<T> )
        {
          return if_else(v < Valmin(as(v)) + 2, Valmax(as(v)), oneminus(v));
        }
      }
    }
    else
    {
      return apply_over(D()(oneminus), v);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // regular
  template<real_value T>
  EVE_FORCEINLINE constexpr T oneminus_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    return oneminus(regular_type(), v);
  }

  // -----------------------------------------------------------------------------------------------
  // saturated masked
  template<real_value T, value COND>
  EVE_FORCEINLINE constexpr T
  oneminus_(EVE_SUPPORTS(cpu_), COND const &cond, saturated_type const &, T const &v) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      if constexpr( floating_value<elt_t> )
      {
        return if_else(cond, oneminus(v), v);
      }
      else
      {
        if constexpr( scalar_value<COND> )
        {
          return cond ? saturated_(oneminus)(v) : v;
        }
        else
        {
          return if_else(cond, saturated_(oneminus)(v), v);
        }
      }
    }
    else
    {
      return aggregate(oneminus, cond, saturated_type(), v);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Basic masked
  template<real_value T, value COND>
  EVE_FORCEINLINE constexpr T oneminus_(EVE_SUPPORTS(cpu_), COND const &cond, T const &v) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      if constexpr( floating_value<elt_t> )
      {
        return if_else(cond, oneminus(v), v);
      }
      else
      {
        if constexpr( scalar_value<COND> )
        {
          return cond ? One(as(v)) - v : v;
        }
        else
        {
          return if_else(cond, One(as(v)) - v, v);
        }
      }
    }
    else
      return apply_over(oneminus, cond, v);
  }

}

#endif
