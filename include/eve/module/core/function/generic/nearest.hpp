//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_NEAREST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_NEAREST_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/is_less.hpp>
#include <eve/constant/twotonmb.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto nearest_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(integral_value<T>)
      {
        return a0;
      }
      else if constexpr(floating_value<T>)
      {
        auto s   = bitofsign(a0);
        auto v   = bit_xor(a0, s);
        auto t2n = Twotonmb(as(a0));
        auto d0  = v + t2n;
        auto d   = d0 - t2n;
        if constexpr(scalar_value<T>)
        {
          return bit_xor((v < t2n) ? d : v, s);
        }
        else
        {
          return bit_xor(if_else(v < t2n, d, v), s);
        }
      }
    }
    else
    {
      return apply_over(nearest, a0);
    }
  }

}

#endif
