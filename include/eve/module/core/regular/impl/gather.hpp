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
  EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const&, U const *ptr, wide<T, N> v) noexcept
  {
    return wide<U, N>{ [=](auto i, auto) { return ptr[v.get(i)]; } };
  }

  template<callable_options O, conditional_expr C, typename U, integral_scalar_value T, typename N>
  EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), C const& cx, O const&, U const *ptr, wide<T, N> v) noexcept
  {
    auto src = alternative(cx, wide<U, N>{}, as<wide<U, N>>{});
    auto m   = expand_mask(cx, as<wide<U, N>>{});

    return wide<U, N>{ [=](auto i, auto) { return m.get(i) ? ptr[v.get(i)] : src.get(i); } };
  }

  //================================================================================================
  // Aligned pointer
  template<callable_options O, typename U, typename S, integral_scalar_value T, typename N>
  EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const& opts, aligned_ptr<U, S> ptr, wide<T, N> v) noexcept
  {
    return gather.behavior(current_api, opts, ptr.get(), v);
  }

  template<callable_options O, conditional_expr C, typename U, typename S, integral_scalar_value T, typename N>
  EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), C const&, O const& opts, aligned_ptr<U, S> ptr, wide<T, N> v) noexcept
  {
    return gather.behavior(current_api, opts, ptr.get(), v);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // scalar index for genericity
  //================================================================================================
  // Unaligned pointer
  template<callable_options O, typename U, integral_scalar_value T>
  EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const&, U const* ptr, T v) noexcept
  {
    return *(ptr + v);
  }

  //================================================================================================
  // Aligned pointer
  template<callable_options O, typename U, typename S, integral_scalar_value T>
  EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const&, aligned_ptr<U, S> ptr, T v) noexcept
  {
    return *(ptr.get() + v);
  }
}
