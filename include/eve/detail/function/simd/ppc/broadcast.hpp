//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, ppc_abi ABI, typename Index>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(vmx_), logical<wide<T,N,ABI>> v, Index) noexcept
  {
    return logical<wide<T,N,ABI>>{ vec_splat(v.storage(), Index::value ) };
  }

  template<typename T, typename N, ppc_abi ABI, typename Index, std::ptrdiff_t C>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(vmx_), logical<wide<T,N,ABI>> v, Index, fixed<C>) noexcept
  {
    using  that_t = logical<wide<T,fixed<C>>;
    return that_t{ vec_splat(v.storage(), Index::value ) };
  }

  template<typename T, typename N, ppc_abi ABI, typename Index>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(vmx_), wide<T,N,ABI> v, Index) noexcept
  {
    return wide<T,N,ABI>{ vec_splat(v.storage(), Index::value ) };
  }

  template<typename T, typename N, ppc_abi ABI, typename Index, std::ptrdiff_t C>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(vmx_), wide<T,N,ABI> v, Index, fixed<C>) noexcept
  {
    using  that_t = wide<T,fixed<C>>;
    return that_t{ vec_splat(v.storage(), Index::value ) };
  }
}
