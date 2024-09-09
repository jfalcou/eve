//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/simd/riscv/make.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{

template<scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
if_else_(EVE_SUPPORTS(rvv_), logical<wide<T, N>> c, wide<T, N> vt, wide<T, N> vf) noexcept
requires rvv_abi<abi_t<T, N>>
{
  return __riscv_vmerge_tu(vt, vf, vt, c, N::value);
}

template<scalar_value T, typename N, scalar_value U>
EVE_FORCEINLINE wide<T, N>
                if_else_(EVE_SUPPORTS(rvv_), logical<wide<T, N>> c, U vt, wide<T, N> vf) noexcept
requires rvv_abi<abi_t<T, N>>
{
  if constexpr( !std::same_as<T, U> ) return if_else(c, static_cast<T>(vt), vf);
  else if constexpr( std::is_floating_point_v<T> ) return __riscv_vfmerge(vf, vt, c, N::value);
  else return __riscv_vmerge(vf, vt, c, N::value);
}

template<scalar_value T, typename N, scalar_value U, scalar_value M>
EVE_FORCEINLINE wide<T, N>
                if_else_(EVE_SUPPORTS(rvv_), logical<wide<T, N>> c, U vt, M vf) noexcept
requires rvv_abi<abi_t<T, N>>
{
  if constexpr( !std::same_as<U, T> || !std::same_as<M, T> )
    return if_else(c, static_cast<T>(vt), static_cast<T>(vf));
  else
  {
    auto fwide = detail::rvv_make_splat(as<wide<T, N>> {}, vf);
    return if_else(c, vt, fwide);
  }
}

template<scalar_value T, typename N>
EVE_FORCEINLINE logical<wide<T, N>>
                if_else_(EVE_SUPPORTS(rvv_),
                         logical<wide<T, N>> c,
                         logical<wide<T, N>> vt,
                         logical<wide<T, N>> vf) noexcept
requires rvv_abi<abi_t<T, N>>
{
  auto needed_vt = __riscv_vmand(c, vt, N::value);
  auto neg_mask  = __riscv_vmnot(c, N::value);
  auto needed_vf = __riscv_vmand(neg_mask, vf, N::value);
  return __riscv_vmor(needed_vt, needed_vf, N::value);
}

}
