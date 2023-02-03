//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<scalar_value T, typename N>
EVE_FORCEINLINE auto
abs_(EVE_SUPPORTS(sve_), wide<T, N> const& a) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( match(c, category::unsigned_) ) return a;
  else return svabs_z(sve_true<T>(),a);
}

template<conditional_expr C, scalar_value T, typename N>
EVE_FORCEINLINE auto
abs_(EVE_SUPPORTS(sve_), C const& cx, wide<T, N> const& v) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();

  if constexpr( match(c, category::unsigned_) ) return v;
  else
  {
    if constexpr( C::is_complete ) return abs_(EVE_RETARGET(cpu_), cx, v);
    else
    {
      auto src = alternative(cx, v, as<wide<T, N>> {});
      auto m   = expand_mask(cx, as<wide<T, N>> {});

      return svabs_m(src,m,v);
    }
  }
}
}
