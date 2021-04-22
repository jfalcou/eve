//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/reduce.hpp>
#include <eve/function/max.hpp>
#include <eve/function/any.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto maximum_ ( EVE_SUPPORTS(cpu_)
                                , splat_type const&, wide<T,N,ABI> const &v
                                ) noexcept
  {
          if constexpr( N::value == 1 )         return v.get(0);
    else  if constexpr( !is_aggregated_v<ABI> ) return splat(basic_reduce)(v, eve::max);
    else
    {
      auto[l,h] = v.slice();
      return  splat(maximum)( eve::max(l,h) );
    }
  }

  template<simd_value T>
  EVE_FORCEINLINE auto maximum_ ( EVE_SUPPORTS(cpu_)
                                , splat_type const&, logical<T> const &v
                                ) noexcept
  {
    return logical<T>(eve::any(v));
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto maximum_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    return v;
  }

  template<real_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto maximum_(EVE_SUPPORTS(cpu_), wide<T,N,ABI> const &v) noexcept
  {
          if constexpr( N::value == 1 )         return v.get(0);
    else  if constexpr( !is_aggregated_v<ABI> ) return basic_reduce(v, eve::max);
    else
    {
      auto[l,h] = v.slice();
      return  maximum( eve::max(l,h) );
    }
  }

  template<simd_value T>
  EVE_FORCEINLINE auto maximum_(EVE_SUPPORTS(cpu_), logical<T> const &v) noexcept
  {
    using v_t = typename logical<T>::value_type;
    return v_t{eve::any(v)};
  }
}
