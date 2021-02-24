//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_scalar_value U, typename N>
  EVE_FORCEINLINE wide<U, N, ppc_> if_else_ ( EVE_SUPPORTS(vmx_)
                                            , logical<wide<U, N, ppc_>> const &m
                                            , wide<U, N, ppc_> const &  v0
                                            , wide<U, N, ppc_> const &  v1
                                            ) noexcept
  {
    return vec_sel(v1.storage(), v0.storage(), bit_cast(m, as_<logical<wide<U,N>>>()).storage());
  }

  template<real_scalar_value U, typename N>
  EVE_FORCEINLINE logical<wide<U, N, ppc_>> if_else_( EVE_SUPPORTS(vmx_)
                                                    , logical<wide<U, N, ppc_>> const & m
                                                    , logical<wide<U, N, ppc_>> const & v0
                                                    , logical<wide<U, N, ppc_>> const & v1
                                                    ) noexcept
  {
    return bit_cast ( vec_sel ( v1.storage(), v0.storage()
                              , bit_cast(m, as_<logical<wide<U,N>>>()).storage()
                              )
                    , as(v0)
                    );
  }
}
