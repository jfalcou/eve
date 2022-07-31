//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T,N> self_bitnot(wide<T,N> const& v) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return vec_nor(v.storage(), v.storage());
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto self_eq(wide<T, N> const &v, wide<T, N> const &w) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return logical<wide<T,N>>(vec_cmpeq(v.storage(), w.storage()));
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto self_neq(vmx_ const&, wide<T, N> const &v, wide<T, N> const &w) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return logical<wide<T,N>>(vec_cmpne(v.storage(), w.storage()));
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto self_less(wide<T, N> const &v, wide<T, N> const &w) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return logical<wide<T,N>>(vec_cmplt(v.storage(), w.storage()));
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto self_greater(wide<T, N> const &v, wide<T, N> const &w) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return logical<wide<T,N>>(vec_cmpgt(v.storage(), w.storage()));
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto self_geq(wide<T, N> const &v, wide<T, N> const &w) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(std::is_floating_point_v<T>)
      return logical< wide<T, N>>(vec_cmpge(v.storage(), w.storage()));
    else
      return !(v < w);
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto self_leq(wide<T, N> const &v, wide<T, N> const &w) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(std::is_floating_point_v<T>)
      return logical<wide<T, N>>(vec_cmple(v.storage(), w.storage()));
    else
      return !(v > w);
  }
}
