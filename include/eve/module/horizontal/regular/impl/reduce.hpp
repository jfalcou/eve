//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorized.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/reduce.hpp>
#include <eve/detail/function/sum.hpp>
#include <eve/function/swap_adjacent_groups.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/function/minimum.hpp>
#include <eve/function/maximum.hpp>
#include <eve/function/splat.hpp>
#include <eve/function/plus.hpp>
#include <eve/function/add.hpp>
#include <eve/module/horizontal/regular/any.hpp>
#include <eve/module/horizontal/regular/all.hpp>

namespace eve::detail
{
  //================================================================================================
  // Find the proper callable if optimization is doable, else return a generic call
  template<typename Callable, typename Option = int>
  EVE_FORCEINLINE auto find_reduction( Callable f, Option = 0) noexcept
  {
          if constexpr( std::same_as<Callable, callable_plus_>        ) return eve::detail::sum;
    else  if constexpr( std::same_as<Callable, callable_add_>         ) return eve::detail::sum;
    else  if constexpr( std::same_as<Callable, callable_min_>         ) return eve::minimum;
    else  if constexpr( std::same_as<Callable, callable_max_>         ) return eve::maximum;
    else  if constexpr( std::same_as<Callable, callable_logical_and_> ) return eve::all;
    else  if constexpr( std::same_as<Callable, callable_logical_or_>  ) return eve::any;
    else  if constexpr( std::same_as<Option, splat_type> )
    {
      return [f]<typename Wide>(splat_type const&, Wide v) { return butterfly_reduction(v,f); };
    }
    else
    {
      return [f]<typename Wide>(Wide v) { return butterfly_reduction(v,f).get(0); };
    }
  }

  template<scalar_value T, typename N, typename Callable>
  EVE_FORCEINLINE auto reduce_( EVE_SUPPORTS(cpu_), splat_type const& s
                              , wide<T,N> v, Callable f
                              ) noexcept
  {
    auto op = find_reduction(f,s);
    return op(s, v);
  }

  template<scalar_value T, typename N, typename Callable>
  EVE_FORCEINLINE auto reduce_(EVE_SUPPORTS(cpu_), wide<T,N> v, Callable f) noexcept
  {
    auto op = find_reduction(f);
    return op(v);
  }

  template<scalar_value T, typename N>
  EVE_FORCEINLINE auto reduce_( EVE_SUPPORTS(cpu_), splat_type const& s, wide<T,N> v ) noexcept
  {
    return eve::detail::sum(s, v);
  }

  template<scalar_value T, typename N>
  EVE_FORCEINLINE auto reduce_(EVE_SUPPORTS(cpu_), wide<T,N> v) noexcept
  {
    return eve::detail::sum(v);
  }

  template<scalar_value T, typename N, typename Callable>
  EVE_FORCEINLINE auto reduce_(EVE_SUPPORTS(cpu_), logical<wide<T,N>> v, Callable f) noexcept
  {
    auto op = find_reduction(f);
    return op(v);
  }
}
