//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/replace.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{
template<typename U, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(sve_), U const* p, wide<T, N> v) noexcept -> wide<U, N>
requires sve_abi<abi_t<T, N>>
{
  return gather[ignore_none](p,v);
}

template<typename U, conditional_expr C, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(sve_), C cx, U const* p, wide<T, N> v) noexcept -> wide<U, N>
requires sve_abi<abi_t<T, N>>
{
  using out_t = wide<U, N>;
  using u_t   = make_integer_t<sizeof(U)>;

  // Ignore All case : just return the alternative if any
  if      constexpr(C::is_complete && !C::is_inverted)  return alternative(cx, out_t{}, as<out_t>{});
  // Aggregation cases
  else if constexpr(has_aggregated_abi_v<out_t>)        return gather_(EVE_RETARGET(cpu_),cx,p,v);
  // Smaller data goes through the generic cases
  else if constexpr(sizeof(U) <= 2)                     return gather_(EVE_RETARGET(cpu_),cx,p,v);
  // Small index get converted then we recall gather
  else if constexpr(sizeof(T) <  4)                     return gather[cx](p, convert(v, as<u_t>{}));
  // SVE gather requires same size for index and values
  else if constexpr(sizeof(T) != sizeof(U))             return gather[cx](p, convert(v, as<u_t>{}));
  else
  {
    auto s = alternative(cx, out_t{}, as<out_t> {});
    auto m = expand_mask(cx, as<out_t> {});

    // Fix up offset
    v *= sizeof(U);
    out_t res = svld1_gather_offset(m, p, v);

    if constexpr(C::has_alternative)  return eve::replace_ignored(res, cx, s);
    else                              return res;
  }
}
}
