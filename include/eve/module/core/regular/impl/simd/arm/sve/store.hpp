//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/unalign.hpp>

namespace eve::detail
{
// Regular store
template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(sve_), wide<T, N> v, Ptr p)
requires(sve_abi<abi_t<T, N>> && !has_store_equivalent<wide<T, N>, Ptr>)
{
  auto ptr = unalign(p);
  if constexpr( N() != expected_cardinal_v<T> )
    store[keep_first(N::value)](bit_cast(v,as<wide<T>>{}),p);
  else
    svst1(sve_true<T>(), ptr, v);
}

// Conditional store
template<scalar_value T,
         typename N,
         relative_conditional_expr       C,
         simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE void
store_(EVE_SUPPORTS(sve_), C const& cond, wide<T, N> const& v, Ptr ptr) noexcept
requires sve_abi<abi_t<T, N>> && (!has_store_equivalent<wide<T, N>, Ptr>)
{
  if constexpr( C::is_complete || C::has_alternative ) store_(EVE_RETARGET(cpu_), cond, v, ptr);
  else if constexpr( N() != expected_cardinal_v<T> )
  {
    store_(EVE_RETARGET(cpu_), cond, v, ptr);
  }
  else
  {
    svst1(cond.mask(as<wide<T, N>>{}), unalign(ptr), v);
  }
}
}
