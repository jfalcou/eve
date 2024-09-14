//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/simd_cast.hpp>

// Return first or second part of vector.

namespace eve::detail
{

//================================================================================================
// Single slice
//================================================================================================

template<callable_options O, typename T, typename N>
EVE_FORCEINLINE wide<T, typename N::split_type>
                slice_(EVE_REQUIRES(rvv_), O const&, wide<T, N> a, lower_slice_t) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto in_lmul  = rvv_lmul_v<T, N>;
  constexpr auto out_lmul = rvv_lmul_v<T, typename N::split_type>;
  if constexpr( in_lmul == out_lmul ) return a.storage();
  else { return simd_cast(a, as<wide<T, typename N::split_type>> {}); }
}

template<callable_options O, typename T, typename N>
EVE_FORCEINLINE wide<T, typename N::split_type>
                slice_(EVE_REQUIRES(rvv_), O const&, wide<T, N> a, upper_slice_t) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto shift_size = N::split_type::value;
  wide<T, N>     res        = __riscv_vslidedown(a, shift_size, N::value);
  constexpr auto in_lmul    = rvv_lmul_v<T, N>;
  constexpr auto out_lmul   = rvv_lmul_v<T, typename N::split_type>;
  if constexpr( in_lmul == out_lmul ) return res.storage();
  else
  {
    // we need to lower lmul - call lmul trunc.
    return simd_cast(res, as<wide<T, typename N::split_type>> {});
  }
}

template<callable_options O, typename T, typename N>
EVE_FORCEINLINE logical<wide<T, typename N::split_type>>
                slice_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>> a, lower_slice_t) noexcept
requires rvv_abi<abi_t<T, N>>
{
  return simd_cast(a, as<logical<wide<T, typename N::split_type>>> {});
}

template<callable_options O, typename T, typename N>
EVE_FORCEINLINE logical<wide<T, typename N::split_type>>
                slice_(EVE_REQUIRES(rvv_), O const&, logical<wide<T, N>> a, upper_slice_t) noexcept
requires rvv_abi<abi_t<T, N>>
{
  auto bits_slice = a.bits().slice(upper_slice_t {});
  // TODO: could be improved when `simd_cast` for RISC-V will support casts between logical-wide.
  auto neq = bits_slice != 0;
  return simd_cast(neq, as<logical<wide<T, typename N::split_type>>> {});
}

//================================================================================================
// Both slice
//================================================================================================

EVE_FORCEINLINE auto
slice_(EVE_REQUIRES(rvv_), callable_options auto const&, simd_value auto x)
{
  return std::array {x.slice(lower_), x.slice(upper_)};
}
}
