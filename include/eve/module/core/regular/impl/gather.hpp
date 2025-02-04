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
  wide<U, N> that = [=](auto i, auto) { return ptr[v.get(i)]; };
  return that;
}

template<callable_options O, conditional_expr C, typename U, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), C const& cx, O const&, U const *ptr, wide<T, N> v) noexcept
{
  auto src = alternative(cx, wide<U, N> {}, as<wide<U, N>> {});
  auto m   = expand_mask(cx, as<wide<U, N>> {});

  wide<U, N> that = [=](auto i, auto) { return m.get(i) ? ptr[v.get(i)] : src.get(i); };
  return that;
}

//================================================================================================
// Aligned pointer
template<callable_options O, typename U, typename S, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const&, aligned_ptr<U, S> ptr, wide<T, N> v) noexcept
{
  return gather(ptr.get(), v);
}

template<callable_options O, conditional_expr C, typename U, typename S, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), C const& cx, O const&, aligned_ptr<U, S> ptr, wide<T, N> v) noexcept
{
  return gather[cx](ptr.get(), v);
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

template<callable_options O, typename U, value X, integral_scalar_value T>
EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const&, logical<X> cond, U const *ptr, T v) noexcept
{
  return cond ? *(ptr + v) : zero(as<U>());
}

//================================================================================================
// Aligned pointer
template<callable_options O, typename U, typename S, integral_scalar_value T>
EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const&, aligned_ptr<U, S> ptr, T v) noexcept
{
  return *(ptr + v);
}

template<callable_options O, typename U, typename S, value X, integral_scalar_value T>
EVE_FORCEINLINE auto gather_(EVE_REQUIRES(cpu_), O const&, logical<X> cond, aligned_ptr<U, S> ptr, T v) noexcept
{
  return cond ? *(ptr + v) : zero(as<U>());
}
}
