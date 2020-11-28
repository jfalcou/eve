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
#include <eve/function/logical_and.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/numeric.hpp>
#include <eve/platform.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto min_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(min, a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE  auto min_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return if_else(is_less(b, a), b, a);
  }

  template<real_simd_value T>
  EVE_FORCEINLINE  auto min_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return apply_over(min, a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // Pedantic
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto min_(EVE_SUPPORTS(cpu_),
                            pedantic_type const &,
                            T const &v0,
                            U const &v1) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic(min), v0, v1);
  }

  template<real_value T>
  EVE_FORCEINLINE auto min_(EVE_SUPPORTS(cpu_),
                            pedantic_type const &,
                            T const &v0,
                            T const &v1) noexcept
  {
    if constexpr(integral_value<T>) return eve::min(v0, v1);
    else
    {
      if constexpr(eve::platform::supports_invalids)
      {
        if constexpr(scalar_value<T>)
        {
          if  (is_eqz(v0) && is_eqz(v1)) return bit_or(v0, v1);
          return is_unordered(v0, v1) ? v0 : eve::min(v0, v1);
        }
        else
        {
          auto tmp = if_else(is_unordered(v0, v1), v0, eve::min(v0, v1));
          return if_else(is_eqz(v0) && is_eqz(v1), bit_or(v0, v1), tmp);
        }
      }
      else
      {
        if constexpr(scalar_value<T>)
        {
          return (is_eqz(v0) && is_eqz(v1) ? bit_or(v0, v1) : eve::min(v0, v1));
        }
        else
        {
          return if_else(is_eqz(v0) && is_eqz(v1), bit_or(v0, v1), eve::min(v0, v1));
        }
      }
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Numeric
  template<typename T, typename U>
  EVE_FORCEINLINE auto min_(EVE_SUPPORTS(cpu_),
                            numeric_type const &,
                            T const &v0,
                            U const &v1) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(numeric(min), v0, v1);
  }

  template<real_value T>
  EVE_FORCEINLINE auto min_(EVE_SUPPORTS(cpu_),
                            numeric_type const &,
                            T const &v0,
                            T const &v1) noexcept
  {
    if constexpr(integral_value<T>) return eve::min(v0, v1);
    else
    {
      if constexpr(eve::platform::supports_invalids)
      {
        if constexpr(scalar_value<T>)
        {
               if (is_nan(v0)) return v1;
          else if (is_nan(v1)) return v0;
          else if (is_eqz(v0) && is_eqz(v1)) return bit_or(v0, v1);
          else return min(v0, v1);
        }
        else
        {
          auto tmp = if_else(is_nan(v0), v1, if_else(is_nan(v1), v0, min(v0, v1)));
          return if_else(is_eqz(v0) && is_eqz(v1), bit_or(v0, v1), tmp);
        }
      }
      else
      {
        if constexpr(scalar_value<T>)
        {
          return (is_eqz(v0) && is_eqz(v1) ? bit_or(v0, v1) : eve::min(v0, v1));
        }
        else
        {
          return if_else(is_eqz(v0) && is_eqz(v1), bit_or(v0, v1), eve::min(v0, v1));
        }
      }
    }
  }
}
