//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/category.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/raw.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Raw version
  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI>  sqrt_(EVE_SUPPORTS(neon128_)
                                        , raw_type const &
                                        , wide<T, N, ABI> const &v0) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

#if defined(__aarch64__)
         if constexpr(cat == category::float64x1 ) return vsqrt_f64(v0);
    else if constexpr(cat == category::float64x2 ) return vsqrtq_f64(v0);

#endif
         if constexpr(cat == category::float32x2 ) return vsqrt_f32(v0);
    else if constexpr(cat == category::float32x4 ) return vsqrtq_f32(v0);
    else                                           return if_else(v0, v0 * raw(rsqrt)(v0), v0);
  }


  //------------------------------------------------------------------------------------------------
  // Basic version
  template<floating_real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI>  sqrt_(EVE_SUPPORTS(neon128_)
                                        , wide<T, N, ABI> const &v0) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

#if defined(__aarch64__)
         if constexpr(cat == category::float64x1 ) return vsqrt_f64(v0);
    else if constexpr(cat == category::float64x2 ) return vsqrtq_f64(v0);

#endif
         if constexpr(cat == category::float32x2 ) return vsqrt_f32(v0);
    else if constexpr(cat == category::float32x4 ) return vsqrtq_f32(v0);
    else {
      auto that = if_else(v0, v0 * raw(rsqrt)(v0), v0);
      if constexpr(platform::supports_invalids)  return if_else(is_not_finite(v0), v0, that);
      else return that;
    }
  }
}
