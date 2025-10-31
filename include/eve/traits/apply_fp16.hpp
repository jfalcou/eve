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
  template <typename Func, typename Arg0, typename... Args>
  constexpr EVE_FORCEINLINE auto apply_fp16_as_fp32(Func&& f, Arg0&& arg0, Args&&... args)
    requires (same_lanes<Arg0, Args...> && std::same_as<element_type_t<Arg0>, eve::float16_t> && (std::same_as<element_type_t<Args>, eve::float16_t> && ...))
  {
    auto r = f(convert(EVE_FWD(arg0), as<float>{}), convert(EVE_FWD(args), as<float>{})...);

    if constexpr (logical_value<decltype(r)>) return convert(r, as<logical<eve::float16_t>>{});
    else                                      return convert(r, as<eve::float16_t>{});
  }

  template <typename Func, typename C, typename Arg0, typename... Args>
  constexpr EVE_FORCEINLINE auto apply_fp16_as_fp32_masked(Func&& f, C const& cx, Arg0&& arg0, Args&&... args)
    requires (same_lanes<Arg0, Args...> && std::same_as<element_type_t<Arg0>, eve::float16_t> && (std::same_as<element_type_t<Args>, eve::float16_t> && ...))
  {
    if constexpr (relative_conditional_expr<C>)
    {
      return apply_fp16_as_fp32(f[cx], arg0, args...);
    }
    else
    {
      auto m = convert(expand_mask(cx, as(arg0)), as<logical<float>>{});
      return apply_fp16_as_fp32(f[m], arg0, args...);
    }
  }

  template <typename Func, typename Arg0, typename... Args>
  constexpr EVE_FORCEINLINE auto apply_fp16_as_u16(Func&& f, Arg0&& arg0, Args&&... args)
    requires (same_lanes<Arg0, Args...> && std::same_as<element_type_t<Arg0>, eve::float16_t> && (std::same_as<element_type_t<Args>, eve::float16_t> && ...))
  {
    auto r = f(bit_cast(EVE_FWD(arg0), as<as_wide_as_t<uint16_t, Arg0>>{}), bit_cast(EVE_FWD(args), as<as_wide_as_t<uint16_t, Args>>{})...);

    if constexpr (logical_value<decltype(r)>) return bit_cast(r, as<as_wide_as_t<logical<eve::float16_t>, decltype(r)>>{});
    else                                      return bit_cast(r, as<as_wide_as_t<eve::float16_t, decltype(r)>>{});
  }
}

