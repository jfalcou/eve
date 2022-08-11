//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
//================================================================================================
// Unaligned pointer
template<typename U, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(cpu_), U const *ptr, wide<T, N> const& v) noexcept
{
  wide<U, N> that = [=](auto i, auto) { return ptr[v.get(i)]; };
  return that;
}

template<typename U, value X, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(cpu_), logical<X> const& cond, U const *ptr, wide<T, N> const& v) noexcept
{
  return if_else(cond, gather(ptr, v), zero_);
}

//================================================================================================
// Aligned pointer
template<typename U, typename S, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(cpu_), aligned_ptr<U, S> ptr, wide<T, N> const& v) noexcept
{
  return gather(ptr.get(), v);
}

template<typename U, typename S, value X, integral_scalar_value T, typename N>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(cpu_),
        logical<X> const& cond,
        aligned_ptr<U, S> ptr,
        wide<T, N> const& v) noexcept
{
  return if_else(cond, gather(ptr.get(), v), zero_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// scalar index for genericity
//================================================================================================
// Unaligned pointer
template<typename U, integral_scalar_value T>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(cpu_), U const *ptr, T const& v) noexcept
{
  return *(ptr + v);
}

template<typename U, value X, integral_scalar_value T>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(cpu_), logical<X> const& cond, U const *ptr, T const& v) noexcept
{
  return cond ? *(ptr + v) : zero(as<U>());
}

//================================================================================================
// Aligned pointer
template<typename U, typename S, integral_scalar_value T>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(cpu_), aligned_ptr<U, S> ptr, T const& v) noexcept
{
  return *(ptr + v);
}

template<typename U, typename S, value X, integral_scalar_value T>
EVE_FORCEINLINE auto
gather_(EVE_SUPPORTS(cpu_), logical<X> const& cond, aligned_ptr<U, S> ptr, T const& v) noexcept
{
  return cond ? *(ptr + v) : zero(as<U>());
}
}
