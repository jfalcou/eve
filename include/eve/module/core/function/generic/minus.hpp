//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_MINUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_MINUS_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/constant/zero.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <type_traits>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T minus_(EVE_SUPPORTS(cpu_)
                                    , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        return static_cast<T>(-a);
      }
      else if constexpr(simd_value<T>)
      {
        if (std::is_floating_point_v<value_type_t<T>>)
        {
          return  bit_xor(a, Signmask(as(a)));
        }
        else
        {
          return Zero(as(a)) - a;
        }
      }
    }
    else  { return apply_over(minus, a); }
  }

  template<real_value T,  typename COND>
  EVE_FORCEINLINE constexpr T minus_(EVE_SUPPORTS(cpu_)
                                    , COND const & cond
                                    , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        return cond ? static_cast<T>(-a) : a;
      }
      else
      {
        return if_else(cond, minus(a), a);
      }
    }
    else  { return apply_over(minus, cond, a); }
  }
}

// Infix operator support
namespace eve
{
  template<value T>
  EVE_FORCEINLINE auto operator-(T const &v) noexcept
  {
    return minus(v);
  }
}

#endif
