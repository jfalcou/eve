//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/arch/float16.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/concept/same_lanes.hpp>
#include <eve/module/core/regular/convert.hpp>

#include <type_traits>

namespace eve::detail
{
  template <typename T>
  concept fp16_should_apply = (std::same_as<T, eve::float16_t> && !detail::supports_fp16_native_type)
                                  || (simd_value<T> && std::same_as<element_type_t<T>, eve::float16_t> && !detail::supports_fp16_vector_ops);

  template <typename Func, typename Arg0, typename... Args>
  constexpr EVE_FORCEINLINE auto apply_fp16_as_fp32(Func&& f, Arg0 arg0, Args... args)
  {
    constexpr auto cvt_args = [](auto v) {
      if constexpr (std::same_as<element_type_t<decltype(v)>, eve::float16_t>)
        return convert(v, as<float>{});
      else
        return v;
    };

    auto r = f(cvt_args(arg0), cvt_args(args)...);
    using r_t = decltype(r);

    if      constexpr (logical_value<r_t>)                       return convert(r, as<logical<eve::float16_t>>{});
    else if constexpr (std::same_as<element_type_t<r_t>, float>) return convert(r, as<eve::float16_t>{});
    else                                                         return r;
  }

  template <typename Func, typename C, typename Arg0, typename... Args>
  constexpr EVE_FORCEINLINE auto apply_fp16_as_fp32_masked(Func&& f, C const& cx, Arg0 arg0, Args... args)
  {
    if constexpr (relative_conditional_expr<C>)
    {
      return apply_fp16_as_fp32(f[cx], arg0, args...);
    }
    else if constexpr (C::has_alternative)
    {
      const auto nc = convert(expand_mask(cx, as(arg0)), as<logical<float>>{});
      const auto na = convert(cx.alternative, as<float>{});
      return apply_fp16_as_fp32(f[if_(nc).else_(na)], arg0, args...);
    }
    else
    {
      auto m = convert(expand_mask(cx, as(arg0)), as<logical<float>>{});
      return apply_fp16_as_fp32(f[m], arg0, args...);
    }
  }

  template <typename Func, typename Arg0, typename... Args>
  constexpr EVE_FORCEINLINE auto apply_fp16_as_u16(Func&& f, Arg0 arg0, Args... args)
  {
    constexpr auto cast_args = [](auto v) {
      if constexpr (std::same_as<element_type_t<decltype(v)>, eve::float16_t>)
        return bit_cast(v, as<as_wide_as_t<uint16_t, decltype(v)>>{});
      else
        return v;
    };

    auto r = f(cast_args(arg0), cast_args(args)...);

    if constexpr (logical_value<decltype(r)>) return bit_cast(r, as<as_wide_as_t<logical<eve::float16_t>, decltype(r)>>{});
    else                                      return bit_cast(r, as<as_wide_as_t<eve::float16_t, decltype(r)>>{});
  }
}
