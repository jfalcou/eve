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
#include <eve/function/min.hpp>
#include <eve/function/all.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto minimum_ ( EVE_SUPPORTS(cpu_)
                                , splat_type const&, wide<T,N,ABI> const &v
                                ) noexcept
  {
    return splat(basic_reduce)(v, eve::min);
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

  template<real_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto minimum_(EVE_SUPPORTS(cpu_), wide<T,N,ABI> const &v) noexcept
  {
    return basic_reduce(v, eve::min);
  }

  template<simd_value T>
  EVE_FORCEINLINE auto minimum_(EVE_SUPPORTS(cpu_), logical<T> const &v) noexcept
  {
    using v_t = typename logical<T>::value_type;
    return v_t{eve::all(v)};
  }
}
