//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/remove_garbage.hpp>

// remove_garbage
namespace eve::detail
{
template<conditional_expr C, typename T, typename N>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(sve_), C const& cond, wide<T, N> v) noexcept -> T
requires sve_abi<abi_t<T, N>>
{
  // Fix mask to not touch garbage lanes if it is not an ignore_*
  auto m = cond.mask(as(v));
  if constexpr(!relative_conditional_expr<C>) m = remove_garbage(cond.mask(as(v)));
  return svmaxv(m, v);
}

template<conditional_expr C, typename T, typename N>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(sve_), C const& cond, splat_type const&, wide<T, N> v) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  return wide<T, N>(maximum[cond](v));
}

template<typename T, typename N>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(sve_), splat_type const&, wide<T, N> v) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  return wide<T, N>(maximum(v));
}

template<typename T, typename N>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(sve_), wide<T, N> v) noexcept -> T
requires sve_abi<abi_t<T, N>>
{
  if constexpr( N::value == 1 ) return v.get(0);
  else if constexpr( N::value == expected_cardinal_v<T> ) return maximum[ignore_none](v);
  else return maximum[keep_first(N::value)](v);
}
}
