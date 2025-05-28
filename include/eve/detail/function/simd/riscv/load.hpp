//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/riscv/rvv_common_masks.hpp>
#include <eve/as.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/safe.hpp>
#include <eve/module/core/regular/unalign.hpp>

namespace eve::detail
{

// Fills undefined values with zeros
template<arithmetic_scalar_value T, typename N, typename PtrTy>
EVE_FORCEINLINE wide<T, N>
                perform_alternative_load(logical<wide<T, N>> mask, as<wide<T, N>>, PtrTy p)
{
  wide<T, N> zero_init {0};
  if constexpr( N::value < eve::fundamental_cardinal_v<T> )
  {
    auto tgt              = as<wide<T, eve::fundamental_cardinal<T>>> {};
    auto fundamental_zero = rvv_make_splat(tgt, static_cast<T>(0));
    zero_init             = bit_cast(fundamental_zero, eve::as<wide<T, N>> {});
  }
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::size8_) ) return __riscv_vle8_tumu(mask, zero_init, p, N::value);
  else if constexpr( match(c, category::size16_) )
    return __riscv_vle16_tumu(mask, zero_init, p, N::value);
  else if constexpr( match(c, category::size32_) )
    return __riscv_vle32_tumu(mask, zero_init, p, N::value);
  else if constexpr( match(c, category::size64_) )
    return __riscv_vle64_tumu(mask, zero_init, p, N::value);
}

// Undefined values are undefined
template<arithmetic_scalar_value T, typename N, typename PtrTy>
EVE_FORCEINLINE wide<T, N>
                perform_load(logical<wide<T, N>> mask, as<wide<T, N>>, PtrTy p)
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::size8_) ) return __riscv_vle8(mask, p, N::value);
  else if constexpr( match(c, category::size16_) ) return __riscv_vle16(mask, p, N::value);
  else if constexpr( match(c, category::size32_) ) return __riscv_vle32(mask, p, N::value);
  else if constexpr( match(c, category::size64_) ) return __riscv_vle64(mask, p, N::value);
}

template<callable_options O,
         arithmetic_scalar_value   T,
         typename N,
         simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE wide<T, N> load_(EVE_REQUIRES(rvv_), O const& opts, Ptr p, as<wide<T, N>> tgt) noexcept
requires(rvv_abi<abi_t<T, N>>)
{
  if constexpr (O::contains(unsafe2))
  {
    return load.behavior(cpu_{}, opts, p, tgt);
  }
  else
  {
    auto ptr = unalign(p);

    if constexpr( C::has_alternative )
    {
      // as later we replace ignored, we can use unsafe load.
      auto load_cond = drop_alternative(cond);
      auto res       = perform_load(load_cond.mask(tgt), tgt, ptr);
      return eve::replace_ignored(res, cond, cond.alternative);
    }
    else if constexpr( C::is_complete && !C::is_inverted ) return wide<T, N>(0);
    else if constexpr( C::is_complete && C::is_inverted )
    {
      return perform_alternative_load(rvv_true<T, N>(), tgt, ptr);
    }
    else return perform_alternative_load(cond.mask(tgt), tgt, ptr);
  }
}

template<callable_options O,
         typename T,
         typename N,
         simd_compatible_ptr<logical<wide<T, N>>> Pointer>
EVE_FORCEINLINE logical<wide<T, N>>
                load_(EVE_REQUIRES(rvv_), O const& opts, Pointer ptr, as<logical<wide<T, N>>> tgt) noexcept
requires rvv_abi<abi_t<T, N>>
{
  if constexpr (O::contains(unsafe2))
  {
    return load.behavior(cpu_{}, opts, ptr, tgt);
  }
  else
  {
    auto cond = opts[condition_key];
    auto const c1    = map_alternative(cond, [](auto alt) { return alt.mask(); });
    auto const block = load[c1](ptr_cast<T const>(ptr), as<wide<T, N>>{});
    return to_logical(block);
  }
}

template<callable_options O, typename Iterator, typename T, typename N>
EVE_FORCEINLINE logical<wide<T, N>>
                load_(EVE_REQUIRES(rvv_), O const& opts, Iterator b, Iterator e, as<logical<wide<T, N>>> tgt) noexcept
requires rvv_abi<abi_t<T, N>>
{
  if constexpr (O::contains(unsafe2))
  {
    return load.behavior(cpu_{}, opts, b, e, tgt);
  }
  else
  {
    auto cond = opts[condition_key];
    auto const c1    = map_alternative(cond, [](auto alt) { return alt.mask(); });
    auto const block = load[c1](b, e, as<wide<T, N>>{});
    return to_logical(block);
  }
}

}
