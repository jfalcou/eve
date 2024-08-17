//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<scalar_value T, typename N, relative_conditional_expr C>
EVE_FORCEINLINE std::ptrdiff_t
                count_true_(EVE_SUPPORTS(cpu_), C cond, logical<wide<T, N>> v) noexcept
requires rvv_abi<abi_t<T, N>>
{
  auto const m = cond.mask(as<wide<T, N>> {});
  return __riscv_vcpop(m, v, N::value);
}

template<scalar_value T, typename N>
EVE_FORCEINLINE std::ptrdiff_t
                count_true_(EVE_SUPPORTS(rvv_), logical<wide<T, N>> v) noexcept
requires rvv_abi<abi_t<T, N>>
{
  return __riscv_vcpop(v, N::value);
}
template<scalar_value T, typename N>
EVE_FORCEINLINE std::ptrdiff_t
                count_true_(EVE_SUPPORTS(rvv_), top_bits<logical<wide<T, N>>> v) noexcept
requires rvv_abi<abi_t<T, N>>
{
  return __riscv_vcpop(v.storage, N::value);
}
}
