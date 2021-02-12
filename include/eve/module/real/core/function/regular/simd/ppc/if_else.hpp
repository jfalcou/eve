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
#include <eve/detail/function/to_logical.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_scalar_value U, typename N>
  EVE_FORCEINLINE wide<U, N, ppc_> if_else_(EVE_SUPPORTS(vmx_),
                                            logical<wide<U, N, ppc_>> const &m,
                                            wide<U, N, ppc_> const &  v0,
                                            wide<U, N, ppc_> const &  v1) noexcept
  {
    return vec_sel(v1.storage(), v0.storage(), bit_cast(m, as_<logical<wide<U,N>>>()).storage());
  }

  template<real_scalar_value U, typename N>
  EVE_FORCEINLINE logical<wide<U, N, ppc_>> if_else_(EVE_SUPPORTS(vmx_),
                                            logical<wide<U, N, ppc_>> const & m,
                                            logical<wide<U, N, ppc_>> const & v0,
                                            logical<wide<U, N, ppc_>> const & v1) noexcept
  {
    return bit_cast(vec_sel(v1.storage(), v0.storage(), bit_cast(m, as_<logical<wide<U,N>>>()).storage()), as(v0));
  }
}
