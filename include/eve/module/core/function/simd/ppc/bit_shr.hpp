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
#include <eve/detail/meta.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<integral_scalar_value T, typename N, integral_scalar_value I>
  EVE_FORCEINLINE auto bit_shr_ ( EVE_SUPPORTS(vmx_),
                                  wide<T, N, ppc_> const &v0,
                                  wide<I, N, ppc_> const &v1
                                ) noexcept
  {
    using i_t = wide<as_integer_t<T, unsigned>, N>;
    return wide<T, N, ppc_>(vec_sr(v0.storage(), bit_cast(v1,as_<i_t>()).storage()));
  }

  template<integral_scalar_value T, typename N, integral_scalar_value I>
  EVE_FORCEINLINE auto bit_shr_(EVE_SUPPORTS(vmx_)
                               , wide<T, N, ppc_> const &v0
                               , I v1) noexcept
  {
    using i_t = wide<as_integer_t<T, unsigned>, N>;
    return shr(v0, i_t(v1));
  }
}

