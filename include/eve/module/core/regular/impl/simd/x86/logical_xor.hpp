//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{
  template<arithmetic_scalar_value T, typename N, scalar_value U, callable_options O>
  EVE_FORCEINLINE auto logical_xor_(EVE_REQUIRES(avx512_),
                                    O                  const& ,
                                    logical<wide<T,N>> const& a,
                                    logical<wide<U,N>> const& b) noexcept
  requires ( x86_abi<abi_t<T,N>> || x86_abi<abi_t<U,N>>)
  {
    if constexpr(std::same_as<T,U>)
    {
      return logical<wide<T,N>>(a.storage() ^ b.storage());
    }
    else
    {
      return logical_xor(a, convert(b,as<logical<T>>{}));                       }
  }
}
