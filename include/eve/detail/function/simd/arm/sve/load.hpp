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
         real_scalar_value         T,
         typename N,
         simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE wide<T, N>
load_(EVE_SUPPORTS(sve_), C const& cond, safe_type const&, eve::as<wide<T, N>> const&, Ptr p)
requires(sve_abi<abi_t<T, N>>)
{
  auto ptr = unalign(p);

  if constexpr(C::is_complete && C::is_inverted)
  {
    if constexpr( N() == expected_cardinal_v<T> ) return svld1(sve_true<T>(), ptr);
    else return svldff1(sve_true<T>(), ptr);
  }
  else
  {
    wide<T, N> loaded;

    if constexpr(!C::is_complete)
    {
      auto mask = cond.mask(as<wide<T,N>>{});
      if constexpr( N() == expected_cardinal_v<T> ) loaded = svld1(mask, ptr);
      else                                          loaded = svldff1(mask, ptr);
      if constexpr( C::has_alternative )
      {
        loaded = svsel(mask, loaded, wide<T,N>(cond.alternative));
      }
    }
    else
    {
      if constexpr( C::has_alternative ) loaded = wide<T,N>(cond.alternative);
    }

    return loaded;
  }
}

//================================================================================================
// Logical support
//================================================================================================
template<relative_conditional_expr C, typename T, typename N, data_source Pointer>
EVE_FORCEINLINE logical<wide<T, N>>
                load_(EVE_SUPPORTS(sve_),
                      C const& cond,
                      safe_type const&,
                      eve::as<logical<wide<T, N>>> const&,
                      Pointer ptr) noexcept
requires(dereference_as<logical<T>, Pointer>::value && sve_abi<abi_t<T, N>>)
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
