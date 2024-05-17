//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<callable_options O, simd_value W, typename Index>
  EVE_FORCEINLINE auto
  broadcast_(EVE_SUPPORTS(vmx_), O const&, W v, Index) noexcept requires ppc_abi<typename W::abi_type>
  {
    return W{vec_splat(v.storage(), Index::value)};
  }

  template<callable_options O, simd_value W, typename Index, std::ptrdiff_t N>
  EVE_FORCEINLINE auto
  broadcast_(EVE_SUPPORTS(vmx_), O const&, W v, Index, fixed<N>) noexcept requires ppc_abi<typename W::abi_type>
  {
    return as_wide_t<W, fixed<N>>{vec_splat(v.storage(), Index::value)};
  }
}
