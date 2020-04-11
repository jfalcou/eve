//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ARG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ARG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto arg_(EVE_SUPPORTS(cpu_)
                                     , D const &
                                     , T const &a) noexcept
  requires std::same_as<D, regular_type> || std::same_as<D, pedantic_type>
  {
    if constexpr(native<T>)
    {
      auto z =  if_else(is_negative(a), Pi(as(a)), eve::zero_);
      if constexpr( platform::supports_nans && std::same_as<D, pedantic_type> )
      {
           return if_else(is_nan(a), eve::allbits_, z);
      }
      else return z:
    }
    else   return apply_over(D()(arg), a);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto arg_(EVE_SUPPORTS(cpu_)
                                     , T const &a) noexcept
  {
    return arg(regular_type, a);
  }
}

#endif
