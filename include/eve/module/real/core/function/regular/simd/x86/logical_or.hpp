//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<scalar_value T, scalar_value U,typename N, x86_abi ABI>
  EVE_FORCEINLINE auto  logical_or_( EVE_SUPPORTS(avx512_)
                                    , logical<wide<T, N, ABI>> const &v0
                                    , logical<wide<U, N, ABI>> const &v1
                                    ) noexcept
  {
    using storage_t = typename logical<wide<T, N, ABI>>::storage_type;
    typename storage_t::type that = v0.storage().value | v1.storage().value;
    return logical<wide<T, N, ABI>>(storage_t{that});
  }
}
