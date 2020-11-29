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

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/pedantic/ldexp.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/mul.hpp>
#include <eve/constant/inf.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Pedantic 128 bits rsqrt
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto rsqrt_(EVE_SUPPORTS(sse2_)
                             , pedantic_type const &
                             , wide<T, N, x86_128_> const &a0) noexcept
  {
     return rsqrt_x86_pedantic(a0);
  }
}
