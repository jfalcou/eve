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
#include <eve/function/bit_xor.hpp>
#include <eve/detail/function/conditional.hpp>
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
          return  bit_xor(a, signmask(eve::as(a)));
        }
        else
        {
          return Zero(eve::as(a)) - a;
        }
      }
    }
    else  { return apply_over(minus, a); }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto minus_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::minus, t);
  }

  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto minus_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    auto substract =  [](auto x, auto y){return x-y;};
    return mask_op( EVE_CURRENT_API{}, cond, substract, t, f);
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
