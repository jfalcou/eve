//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/simd_cast.hpp>
#include <eve/module/core/regular/is_greater_equal.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_less_equal.hpp>
#include <eve/module/core/regular/is_less.hpp>

namespace eve::detail
{
  template<callable_options O, floating_scalar_value T, typename N, typename F>
  EVE_FORCEINLINE logical<wide<T, N>> compare_absolute_(EVE_REQUIRES(neon128_), O const& opts,
                                                        wide<T, N> v, wide<T, N> w, F f) noexcept
  requires (arm_abi<abi_t<T, N>>)
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr(F{} == is_less_equal)
    {
      if constexpr( c == category::float32x2  ) return vcale_f32 (v, w);
      else if constexpr( c == category::float32x4  ) return vcaleq_f32(v, w);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vcale_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vcaleq_f64 (v, w);
      }
      else return compare_absolute.behavior(as<logical<wide<T, N>>>{}, cpu_{}, v, w, f);
    }
    else if constexpr(F{} ==  is_greater_equal)
    {
      if constexpr( c == category::float32x2  ) return vcage_f32 (v, w);
      else if constexpr( c == category::float32x4  ) return vcageq_f32(v, w);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vcage_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vcageq_f64 (v, w);
      }
      else return compare_absolute.behavior(as<logical<wide<T, N>>>{}, cpu_{}, v, w, f);
    }
    else if constexpr(F{} == is_less)
    {
      if constexpr( c == category::float32x2  ) return vcalt_f32 (v, w);
      else if constexpr( c == category::float32x4  ) return vcaltq_f32(v, w);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vcalt_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vcaltq_f64 (v, w);
      }
      else return compare_absolute.behavior(as<logical<wide<T, N>>>{}, cpu_{}, v, w, f);
    }
    else if constexpr(F{} == is_greater)
    {
      if constexpr( c == category::float32x2  ) return vcagt_f32 (v, w);
      else if constexpr( c == category::float32x4  ) return vcagtq_f32(v, w);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vcagt_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vcagtq_f64 (v, w);
      }
      else return compare_absolute.behavior(as<logical<wide<T, N>>>{}, cpu_{}, v, w, f);
    }
    else return compare_absolute.behavior(as<logical<wide<T, N>>>{}, cpu_{}, v, w, f);
  }
}
