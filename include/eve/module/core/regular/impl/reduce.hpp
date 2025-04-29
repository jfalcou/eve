//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorized.hpp>
#include <eve/detail/function/reduce.hpp>
#include <eve/detail/function/sum.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/module/core/regular/logical_or.hpp>
#include <eve/module/core/regular/maximum.hpp>
#include <eve/module/core/regular/minimum.hpp>
#include <eve/module/core/regular/splat.hpp>
#include <eve/module/core/named_shuffles/swap_adjacent.hpp>

namespace eve::detail
{
//================================================================================================
// Find the proper callable if optimization is doable, else return a generic call
template<typename Callable, typename Option = int>
EVE_FORCEINLINE auto
find_reduction(Callable f, Option = 0) noexcept
{
  if constexpr( std::same_as<Callable, callable_add_> ) return eve::detail::sum;
  else if constexpr( std::same_as<Callable, decltype(min)> ) return eve::minimum;
  else if constexpr( std::same_as<Callable, decltype(max)> ) return eve::maximum;
  else if constexpr( std::same_as<Callable, decltype(logical_and)> ) return eve::all;
  else if constexpr( std::same_as<Callable, decltype(logical_or)> ) return eve::any;
  else if constexpr( std::same_as<Option, splat_type> )
  {
    return [f]<typename Wide>(splat_type const&, Wide v) { return butterfly_reduction(v, f); };
  }
  else
  {
    return [f]<typename Wide>(Wide v) { return butterfly_reduction(v, f).get(0); };
  }
}

template<scalar_value T, typename N, typename Callable>
EVE_FORCEINLINE auto
reduce_(EVE_SUPPORTS(cpu_), splat_type const& s, wide<T, N> v, Callable f) noexcept
{
  if constexpr (std::same_as<Callable, callable_add_>) return eve::detail::sum[splat2](v);
  else
  {
    auto op = find_reduction(f, s);
    return op(s, v);
  }
}

template<scalar_value T, typename N, typename Callable>
EVE_FORCEINLINE auto
reduce_(EVE_SUPPORTS(cpu_), wide<T, N> v, Callable f) noexcept
{
  auto op = find_reduction(f);
  return op(v);
}

template<scalar_value T, typename N>
EVE_FORCEINLINE auto
reduce_(EVE_SUPPORTS(cpu_), splat_type const& s, wide<T, N> v) noexcept
{
  return eve::detail::sum[splat2](v);
}

template<scalar_value T, typename N>
EVE_FORCEINLINE auto
reduce_(EVE_SUPPORTS(cpu_), wide<T, N> v) noexcept
{
  return eve::detail::sum(v);
}

template<scalar_value T, typename N, typename Callable>
EVE_FORCEINLINE auto
reduce_(EVE_SUPPORTS(cpu_), logical<wide<T, N>> v, Callable f) noexcept
{
  auto op = find_reduction(f);
  return op(v);
}
}
