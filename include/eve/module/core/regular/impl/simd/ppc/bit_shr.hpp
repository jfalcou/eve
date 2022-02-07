//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/shr.hpp>
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
                                  wide<T, N> const &v0,
                                  wide<I, N> const &v1
                                ) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    using i_t = wide<as_integer_t<T, unsigned>, N>;
    return wide<T, N>(vec_sr(v0.storage(), bit_cast(v1,as<i_t>()).storage()));
  }

  template<integral_scalar_value T, typename N, integral_scalar_value I>
  EVE_FORCEINLINE auto bit_shr_(EVE_SUPPORTS(vmx_)
                               , wide<T, N> const &v0
                               , I v1) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    using i_t = wide<as_integer_t<T, unsigned>, N>;
    return bit_shr(v0, i_t(v1));
  }
}
