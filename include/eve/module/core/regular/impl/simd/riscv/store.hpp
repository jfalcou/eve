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

template<arithmetic_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void
riscv_store(wide<T, N> v, Ptr p)
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::size8_) ) return __riscv_vse8(p, v, N::value);
  if constexpr( match(c, category::size16_) ) return __riscv_vse16(p, v, N::value);
  if constexpr( match(c, category::size32_) ) return __riscv_vse32(p, v, N::value);
  if constexpr( match(c, category::size64_) ) return __riscv_vse64(p, v, N::value);
}

// Regular store
template<relative_conditional_expr C, arithmetic_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void store_impl(rvv_, C const& cx, wide<T, N> v, Ptr ptr)
  requires (rvv_abi<abi_t<T, N>> && !has_store_equivalent<wide<T, N>, Ptr>)
{
  auto p = unalign(ptr);

  if constexpr( C::is_complete )
  {
    if constexpr( !C::is_inverted ) return;
    else return riscv_store(v, p);
  }
  else if constexpr( C::has_alternative )
  {
    auto full_data = eve::replace_ignored(v, cx, cx.alternative);
    return riscv_store(full_data, p);
  }
  else riscv_store(cx.mask(as<wide<T, N>> {}), v, p);
}
}
