//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename U, typename N>
  EVE_FORCEINLINE wide<T, N> bit_select_(EVE_SUPPORTS(vmx_),
                                        wide<U, N> const &m,
                                        wide<T, N> const &v0,
                                        wide<T, N> const &v1) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    using i_t = wide<as_integer_t<T, unsigned>, N>;

    return vec_sel(v1.storage(), v0.storage(), bit_cast(m,as<i_t>()).storage());
  }
}
