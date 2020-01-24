//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DEC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_DEC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/add.hpp>
#include <eve/constant/one.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto dec_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    return v - One(as(v));
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<typename U, typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto dec_(EVE_SUPPORTS(cpu_), U const &cond, wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(!is_vectorized_v<U>)
    {
      return cond ? dec(v) : v;
    }
    else if constexpr(std::is_integral_v<T>)
    {
      return v + (bit_mask(bit_cast(cond,as(v))));
    }
    else
    {
      return if_else(cond, v - One(as(v)), v);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated case
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  dec_(EVE_SUPPORTS(cpu_), saturated_type const &, wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      return dec(a);
    }
    else
    {
      return dec[ a != Valmin(as(a)) ](a);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Saturated Masked case
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto
  dec_(EVE_SUPPORTS(cpu_), U const &cond, saturated_type const &, wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(!is_vectorized_v<U>)
    {
      if constexpr(std::is_floating_point_v<T>)
      {
        return cond ? dec(a) : a;
      }
      else
      {
        auto tst = is_not_equal(Valmin(as(a)), a);
        return cond ? dec[ tst ](a) : a;
      }
    }
    else
    {
      if constexpr(std::is_floating_point_v<T>)
      {
        return dec[ cond ](a);
      }
      else
      {
        auto tst = is_not_equal(Valmin(as(a)), a);
        return dec[ logical_and(tst, cond) ](a);
      }
    }
  }
}

#endif
