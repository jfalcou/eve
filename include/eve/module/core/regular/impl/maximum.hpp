//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/reduce.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/splat.hpp>

namespace eve::detail
{
template<real_scalar_value T, typename N>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(cpu_), splat_type const&, wide<T, N> const& v) noexcept
{
  if constexpr( N::value == 1 ) return v;
  else if constexpr( !is_aggregated_v<abi_t<T, N>> ) return butterfly_reduction(v, eve::max);
  else
  {
    auto [l, h] = v.slice();
    auto r      = splat(maximum)(eve::max(l, h));
    return eve::combine(r, r);
  }
}

template<simd_value T>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(cpu_), splat_type const&, logical<T> const& v) noexcept
{
  return logical<T>(eve::any(v));
}

template<real_scalar_value T>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(cpu_), T const& v) noexcept
{
  return v;
}

template<real_scalar_value T, typename N>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(cpu_), wide<T, N> const& v) noexcept
{
  if constexpr( N::value == 1 ) return v.get(0);
  else if constexpr( !is_aggregated_v<abi_t<T, N>> ) return butterfly_reduction(v, eve::max).get(0);
  else
  {
    auto [l, h] = v.slice();
    return maximum(eve::max(l, h));
  }
}

template<simd_value T>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(cpu_), logical<T> const& v) noexcept
{
  return eve::any(v);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return maximum(if_else(cond, t, eve::valmin));
}

template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
maximum_(EVE_SUPPORTS(cpu_), C const& cond, splat_type const&, U const& t) noexcept
{
  return splat(maximum)(if_else(cond, t, eve::valmin));
}

}
