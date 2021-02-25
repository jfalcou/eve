//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE wide<T,N,ABI> self_bitnot(wide<T,N,ABI> const& v) noexcept
  {
    return vec_nor(v.storage(), v.storage());
  }

  template<real_scalar_value T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE auto self_eq(wide<T, N, ABI> const &v, wide<T, N, ABI> const &w) noexcept
  {
    return logical<wide<T,N,ABI>>(vec_cmpeq(v.storage(), w.storage()));
  }

  template<real_scalar_value T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE auto self_neq(wide<T, N, ABI> const &v, wide<T, N, ABI> const &w) noexcept
  {
    return logical<wide<T,N,ABI>>(vec_cmpne(v.storage(), w.storage()));
  }

  template<real_scalar_value T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE auto self_less(wide<T, N, ABI> const &v, wide<T, N, ABI> const &w) noexcept
  {
    return logical<wide<T,N,ABI>>(vec_cmplt(v.storage(), w.storage()));
  }

  template<real_scalar_value T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE auto self_greater(wide<T, N, ABI> const &v, wide<T, N, ABI> const &w) noexcept
  {
    return logical<wide<T,N,ABI>>(vec_cmpgt(v.storage(), w.storage()));
  }

  template<real_scalar_value T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE auto self_geq(wide<T, N, ABI> const &v, wide<T, N, ABI> const &w) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
      return logical< wide<T, N, ABI>>(vec_cmpge(v.storage(), w.storage()));
    else
      return !(v < w);
  }

  template<real_scalar_value T, typename N, ppc_abi ABI>
  EVE_FORCEINLINE auto self_leq(wide<T, N, ABI> const &v, wide<T, N, ABI> const &w) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
      return logical< wide<T, N, ABI>>(vec_cmple(v.storage(), w.storage()));
    else
      return !(v > w);
  }
}
