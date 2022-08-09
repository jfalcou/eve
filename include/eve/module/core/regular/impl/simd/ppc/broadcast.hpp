//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
template<typename T, typename N, typename Index>
EVE_FORCEINLINE auto
broadcast_(EVE_SUPPORTS(vmx_), logical<wide<T, N>> v, Index) noexcept requires ppc_abi<abi_t<T, N>>
{
  return logical<wide<T, N>> {vec_splat(v.storage(), Index::value)};
}

template<typename T, typename N, typename Index, std::ptrdiff_t C>
EVE_FORCEINLINE auto
broadcast_(EVE_SUPPORTS(vmx_),
           logical<wide<T, N>> v,
           Index,
           fixed<C>) noexcept requires ppc_abi<abi_t<T, N>>
{
  using that_t = logical<wide<T, fixed<C>>>;
  return that_t {vec_splat(v.storage(), Index::value)};
}

template<typename T, typename N, typename Index>
EVE_FORCEINLINE auto
broadcast_(EVE_SUPPORTS(vmx_), wide<T, N> v, Index) noexcept requires ppc_abi<abi_t<T, N>>
{
  return wide<T, N> {vec_splat(v.storage(), Index::value)};
}

template<typename T, typename N, typename Index, std::ptrdiff_t C>
EVE_FORCEINLINE auto
broadcast_(EVE_SUPPORTS(vmx_), wide<T, N> v, Index, fixed<C>) noexcept requires ppc_abi<abi_t<T, N>>
{
  using that_t = wide<T, fixed<C>>;
  return that_t {vec_splat(v.storage(), Index::value)};
}
}
