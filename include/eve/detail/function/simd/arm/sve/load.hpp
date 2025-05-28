//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/unalign.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE wide<T, N> load_(EVE_REQUIRES(sve_), O const& opts, Ptr p, as<wide<T, N>> tgt) noexcept
    requires (sve_abi<abi_t<T, N>>)
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto c = opts[condition_key];
    auto ptr = unalign(p);

    if constexpr (O::contains(unsafe2))
    {
      return load.behavior(cpu_{}, opts, p, tgt);
    }
    else if constexpr ( C::has_alternative )
    {
      auto res = load(drop_alternative(cond), s, tgt, p);
      return eve::replace_ignored(res, cond, cond.alternative);
    }
    else if constexpr ( C::is_complete && !C::is_inverted ) return {};
    else if constexpr(C::is_complete && C::is_inverted && N() == expected_cardinal_v<T> )
    {
      return svld1(sve_true<T>(), ptr);
    }
    else return svld1(expand_mask(cond, tgt), ptr);
  }

  //================================================================================================
  // Logical support
  //================================================================================================
  template<callable_options O, typename T, typename N, simd_compatible_ptr<logical<wide<T, N>>> Pointer>
  EVE_FORCEINLINE logical<wide<T, N>> load_(EVE_REQUIRES(sve_), O const& opts, Pointer ptr, as<logical<wide<T, N>>> tgt) noexcept
  {
    if constexpr (O::contains(unsafe2))
    {
      return load.behavior(cpu_{}, opts, ptr, tgt);
    }
    else
    {
      using C = rbr::result::fetch_t<condition_key, O>;
      auto c = opts[condition_key];

      auto const c1     = map_alternative(cond, [](auto alt) { return alt.mask(); });
      auto const block  = load(c1, safe, eve::as<wide<T, N>> {}, ptr_cast<T const>(ptr));
      return to_logical(block);
    }
  }

  template<callable_options O, typename Iterator, typename T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> load_(EVE_REQUIRES(sve_), O const& opts, Iterator b, Iterator e, as<logical<wide<T, N>>> tgt) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(unsafe2))
    {
      return load.behavior(cpu_{}, opts, b, e, tgt);
    }
    else
    {
      using C = rbr::result::fetch_t<condition_key, O>;
      auto c = opts[condition_key];

      auto const c1     = map_alternative(cond, [](auto alt) { return alt.mask(); });
      auto const block  = load(c1, safe, eve::as<wide<T, N>> {}, b, e);
      return to_logical(block);
    }
  }
}
