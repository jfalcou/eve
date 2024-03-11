//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/arch/riscv/rvv_common_masks.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/unalign.hpp>

namespace eve::detail
{

template<arithmetic_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void
riscv_store(logical<wide<T, N>> mask, wide<T, N> v, Ptr p)
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::size8_) ) return __riscv_vse8(mask, p, v, N::value);
  if constexpr( match(c, category::size16_) ) return __riscv_vse16(mask, p, v, N::value);
  if constexpr( match(c, category::size32_) ) return __riscv_vse32(mask, p, v, N::value);
  if constexpr( match(c, category::size64_) ) return __riscv_vse64(mask, p, v, N::value);
}

// Regular store
template<arithmetic_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(rvv_), wide<T, N> v, Ptr p)
requires(rvv_abi<abi_t<T, N>> && !has_store_equivalent<wide<T, N>, Ptr>)
{
  auto const tgt = as<wide<T>> {};
  auto       ptr = unalign(p);

  return riscv_store(rvv_true<T, N>(), v, p);
}

// Conditional store
template<scalar_value T,
         typename N,
         relative_conditional_expr       C,
         simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(rvv_), C const& cond, wide<T, N> const& v, Ptr ptr) noexcept
requires rvv_abi<abi_t<T, N>> && (!has_store_equivalent<wide<T, N>, Ptr>)
{
  if constexpr( C::is_complete || C::has_alternative || N() != expected_cardinal_v<T> )
  {
    store_(EVE_RETARGET(cpu_), cond, v, ptr);
  }
  else riscv_store(cond.mask(as<wide<T, N>> {}), v, unalign(ptr));
}

}
