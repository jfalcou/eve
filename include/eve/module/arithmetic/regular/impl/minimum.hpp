//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/min.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto minimum_ ( EVE_SUPPORTS(cpu_)
                                , splat_type const&, wide<T,N> const &v
                                ) noexcept
  {
          if constexpr( N::value == 1 )         return v;
    else  if constexpr( !is_aggregated_v<abi_t<T, N>> ) return butterfly_reduction(v, eve::min);
    else
    {
      auto[l,h] = v.slice();
      auto r = splat(minimum)( eve::min(l,h) );
      return eve::combine(r,r);
    }
  }

  template<simd_value T>
  EVE_FORCEINLINE auto minimum_ ( EVE_SUPPORTS(cpu_)
                                , splat_type const&, logical<T> const &v
                                ) noexcept
  {
    return logical<T>(eve::all(v));
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto minimum_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    return v;
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto minimum_(EVE_SUPPORTS(cpu_), wide<T,N> const &v) noexcept
  {
          if constexpr( N::value == 1 )         return v.get(0);
    else  if constexpr( !is_aggregated_v<abi_t<T, N>> ) return butterfly_reduction(v, eve::min).get(0);
    else
    {
      auto[l,h] = v.slice();
      return  minimum( eve::min(l,h) );
    }
  }

  template<simd_value T>
  EVE_FORCEINLINE auto minimum_(EVE_SUPPORTS(cpu_), logical<T> const &v) noexcept
  {
    return eve::all(v);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto minimum_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return minimum(if_else(cond, t, eve::valmax));
  }

  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto minimum_(EVE_SUPPORTS(cpu_), C const &cond
                               , splat_type const&, U const &t) noexcept
  {
    return splat(minimum)(if_else(cond, t, eve::valmax));
  }
}
