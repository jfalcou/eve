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
#include <eve/detail/meta.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto arg_(EVE_SUPPORTS(cpu_)
                                     , T const &a) noexcept
  {
    return if_else(is_negative(a), Pi(as(a)), eve::zero_);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto arg_(EVE_SUPPORTS(cpu_)
                                     , pedantic_type const&
                                     , T const &a) noexcept
  {
    auto r = arg(a);
    if constexpr( platform::supports_nans )
    {
      return if_else(is_nan(a), eve::allbits_, r);
    }
    else
    {
      return r;
    }
  }
}

#endif
