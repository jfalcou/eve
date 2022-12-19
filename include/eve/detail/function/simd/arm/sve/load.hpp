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
template<relative_conditional_expr C,
         arithmetic_scalar_value   T,
         typename N,
         simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE wide<T, N>
load_(EVE_SUPPORTS(sve_),
  C const& cond, safe_type const& s, eve::as<wide<T, N>> const& tgt, Ptr p)
  requires (sve_abi<abi_t<T, N>>)
{
  auto ptr = unalign(p);

  if constexpr ( C::has_alternative )
  {
    auto res = load(drop_alternative(cond), s, tgt, p);
    return eve::replace_ignored(res, cond, cond.alternative);
  }
  else if constexpr ( C::is_complete && !C::is_inverted ) return {};
  else if constexpr(C::is_complete && C::is_inverted && N() == expected_cardinal_v<T> )
  {
    return svld1(sve_true<T>(), ptr);
  }
  else return svld1(cond.mask(tgt), ptr);
}

//================================================================================================
// Logical support
//================================================================================================
template<relative_conditional_expr C, typename T, typename N,
      simd_compatible_ptr<logical<wide<T, N>>> Pointer>
EVE_FORCEINLINE logical<wide<T, N>>
                load_(EVE_SUPPORTS(sve_),
                      C const& cond,
                      safe_type const&,
                      eve::as<logical<wide<T, N>>> const&,
                      Pointer ptr) noexcept
{
  auto const c1     = map_alternative(cond, [](auto alt) { return alt.mask(); });
  auto const block  = load(c1, safe, eve::as<wide<T, N>> {}, ptr_cast<T const>(ptr));
  return to_logical(block);
}

template<relative_conditional_expr C,typename Iterator, typename T, typename N>
EVE_FORCEINLINE logical<wide<T, N>>
                load_(EVE_SUPPORTS(sve_),
                      C const& cond,
                      safe_type const&,
                      eve::as<logical<wide<T, N>>> const&,
                      Iterator b,
                      Iterator e) noexcept
requires sve_abi<abi_t<T, N>>
{
  auto const c1     = map_alternative(cond, [](auto alt) { return alt.mask(); });
  auto const block  = load(c1, safe, eve::as<wide<T, N>> {}, b, e);
  return to_logical(block);
}
}
