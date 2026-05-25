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
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve::_
{

template<arithmetic_scalar_value T, size_type N, simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void
riscv_store(logical<wide<T, N>> mask, wide<T, N> v, Ptr p)
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr(std::same_as<T, eve::float16_t> && !supports_fp16_vector_conversion)
  {
    const auto nm = bit_cast(mask, as<logical<wide<uint16_t, N>>>{});
    const auto nv = bit_cast(v, as<wide<uint16_t, N>>{});
    __riscv_vse16(nm, p, nv, N);
  }
  else if constexpr( match(c, category::size8_) ) __riscv_vse8(mask, p, v, N);
  else if constexpr( match(c, category::size16_) ) __riscv_vse16(mask, p, v, N);
  else if constexpr( match(c, category::size32_) ) __riscv_vse32(mask, p, v, N);
  else if constexpr( match(c, category::size64_) ) __riscv_vse64(mask, p, v, N);
}

template<arithmetic_scalar_value T, size_type N, simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void
riscv_store(wide<T, N> v, Ptr p)
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( std::same_as<T, eve::float16_t> && !supports_fp16_vector_conversion)
  {
    const auto nv = bit_cast(v, as<wide<uint16_t, N>>{});
    __riscv_vse16(p, nv, N::value);
  }
  else if constexpr( match(c, category::size8_) ) __riscv_vse8(p, v, N);
  else if constexpr( match(c, category::size16_) ) __riscv_vse16(p, v, N);
  else if constexpr( match(c, category::size32_) ) __riscv_vse32(p, v, N);
  else if constexpr( match(c, category::size64_) ) __riscv_vse64(p, v, N);
}

// Regular store
template<relative_conditional_expr C, arithmetic_scalar_value T, size_type N, simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void store_impl(rvv_, C const& cx, wide<T, N> v, Ptr ptr)
  requires (rvv_abi<abi_t<T, N>> && !has_store_equivalent<wide<T, N>, Ptr>)
{
  auto p = unalign(ptr);

  if constexpr( C::is_complete )
  {
    if constexpr( !C::is_inverted ) return;
    else riscv_store(v, p);
  }
  else if constexpr( C::has_alternative )
  {
    auto full_data = eve::replace_ignored(v, cx, cx.alternative);
    riscv_store(full_data, p);
  }
  else riscv_store(cx.mask(as<wide<T, N>> {}), v, p);
}
}
