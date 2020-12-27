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

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE logical<wide<T, N, ABI>>  logical_not_( EVE_SUPPORTS(avx512_)
                                                        , logical<wide<T, N, ABI>> const &v0
                                                        ) noexcept
  {
    using s_t = typename logical<wide<T,N,ABI>>::storage_type;
    using i_t = typename s_t::type;
    return s_t{~i_t(v0.storage().value)};
  }
}
