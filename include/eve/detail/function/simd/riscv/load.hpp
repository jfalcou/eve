//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/intrinsic_wrappers/riscv/rvv_common_masks.hpp>
#include <eve/module/core/regular/safe.hpp>
#include <eve/module/core/regular/unalign.hpp>

EVE_NAMESPACE::_
{

// Fills undefined values with zeros
template<arithmetic_scalar_value T, width_type N, typename PtrTy>
wide<T, N> perform_alternative_load(logical<wide<T, N>> mask, as<wide<T, N>>, PtrTy p)
{
  wide<T, N> zero_init {0};
  if constexpr( N < eve::fundamental_width_v<T> )
  {
    auto tgt              = as<wide<T, eve::fundamental_width_v<T>>> {};
    auto fundamental_zero = rvv_make_splat(tgt, static_cast<T>(0));
    zero_init             = bit_cast(fundamental_zero, eve::as<wide<T, N>> {});
  }
  constexpr auto c = categorize<wide<T, N>>();
        if constexpr( match(c, category::size8_)  ) return __riscv_vle8_tumu(mask, zero_init, p, N);
  else  if constexpr( match(c, category::size16_) ) return __riscv_vle16_tumu(mask, zero_init, p, N);
  else  if constexpr( match(c, category::size32_) ) return __riscv_vle32_tumu(mask, zero_init, p, N);
  else  if constexpr( match(c, category::size64_) ) return __riscv_vle64_tumu(mask, zero_init, p, N);
}

// Undefined values are undefined
template<arithmetic_scalar_value T, width_type N, typename PtrTy>
wide<T, N> perform_load(logical<wide<T, N>> mask, as<wide<T, N>>, PtrTy p)
{
  constexpr auto c = categorize<wide<T, N>>();
        if constexpr( match(c, category::size8_)  ) return __riscv_vle8(mask, p, N);
  else  if constexpr( match(c, category::size16_) ) return __riscv_vle16(mask, p, N);
  else  if constexpr( match(c, category::size32_) ) return __riscv_vle32(mask, p, N);
  else  if constexpr( match(c, category::size64_) ) return __riscv_vle64(mask, p, N);
}

template<typename T, width_type N, simd_compatible_ptr<wide<T, N>> Ptr>
wide<T, N> load_impl(rvv_, Ptr p, as<wide<T, N>> tgt) noexcept
  requires rvv_abi<abi_t<T, N>>
{
  return perform_alternative_load(rvv_true<T, N>(), tgt, unalign(p));
}

template<typename T, width_type N, typename Alt>
wide<T, N> load_masked_impl(rvv_, logical<wide<T, N>> m, Alt alt, T const* p, as<wide<T, N>> tgt) noexcept
  requires rvv_abi<abi_t<T, N>>
{
  if constexpr( std::same_as<Alt, wide<T, N>> ) return if_else(m, perform_load(m, tgt, p), alt);
  else                                          return perform_alternative_load(m, tgt, p);
}

}
