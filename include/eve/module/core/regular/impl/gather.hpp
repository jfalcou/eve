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
#include <eve/detail/implementation.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/module/core/constant/zero.hpp>

namespace eve::detail
{
  //================================================================================================
  // Unaligned pointer
  template<callable_options O, typename U, integral_scalar_value T, typename N>
  EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const& opts, U const *ptr, wide<T, N> v) noexcept
  {
    auto cx = opts[condition_key];

    if constexpr (std::same_as<decltype(cx), ignore_none_>)
    {
      return wide<U, N>{ [=](auto i, auto) { return ptr[v.get(i)]; } };
    }
    else
    {
      auto src = alternative(cx, wide<U, N>{}, as<wide<U, N>>{});

      if constexpr (std::same_as<decltype(cx), ignore_all_>)
      {
        return src;
      }
      else
      {
        auto m = expand_mask(cx, as<wide<U, N>>{});
        return wide<U, N>{ [=](auto i, auto) { return m.get(i) ? ptr[v.get(i)] : src.get(i); } };
      }
    }
  }

  //================================================================================================
  // Aligned pointer
  template<callable_options O, typename U, typename S, integral_scalar_value T, typename N>
  EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const& opts, aligned_ptr<U, S> ptr, wide<T, N> v) noexcept
  {
    return gather.behavior(current_api, opts, ptr.get(), v);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // scalar index for genericity
  //================================================================================================
  // Unaligned pointer
  template<callable_options O, typename U, integral_scalar_value T>
  EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const& opts, U const* ptr, T v) noexcept
  {
    using C = rbr::result::fetch_t<condition_key, O>;

    if constexpr (std::same_as<C, ignore_none_>) return ptr[v];
    else
    {
      const auto cx = opts[condition_key];
      const auto src = alternative(cx, U{}, as<U>{});
      return expand_mask(cx, as<U>{}) ? ptr[v] : src;
    }
  }

  //================================================================================================
  // Aligned pointer
  template<callable_options O, typename U, typename S, integral_scalar_value T>
  EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const& opts, aligned_ptr<U, S> ptr, T v) noexcept
  {
    return gather.behavior(current_api, opts, ptr.get(), v);
  }
}
