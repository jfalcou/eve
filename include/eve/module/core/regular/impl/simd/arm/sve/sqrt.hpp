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
template<conditional_expr C, value V>
EVE_FORCEINLINE auto
sqrt_(EVE_SUPPORTS(sve_), C const& cond, V const& v) noexcept -> V
requires sve_abi<typename V::abi_type>
{
  if constexpr( C::is_complete )
  {
    if constexpr( C::is_inverted )  return svsqrt_x(sve_true<element_type_t<V>>(), v);
    else                            return alternative(cond, v, as<V> {});
  }
  else
  {
    auto src = alternative(cond, v, as<V> {});
    auto m   = expand_mask(cond, as<V> {});
    return svsqrt_m(src, m, v);
  }
}

template<floating_scalar_value T, typename N>
EVE_FORCEINLINE auto
sqrt_(EVE_SUPPORTS(sve_), wide<T, N> const& v) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  return sqrt[ignore_none](v);
}

}
