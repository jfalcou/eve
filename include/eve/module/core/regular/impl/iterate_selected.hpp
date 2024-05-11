//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/conditional.hpp>

#include <bit>

namespace eve::detail
{

template<typename F> struct plus_offset_lambda
{
  F&             f;
  std::ptrdiff_t offset;

  EVE_FORCEINLINE
  bool operator()(std::ptrdiff_t i) const { return f(i + offset); }
};

template<std::ptrdiff_t bits_per_element, std::unsigned_integral Bits>
EVE_FORCEINLINE bool
iterate_selected_int(Bits bits, auto&& f)
{
  if constexpr( bits_per_element <= 2 )
  {
    while( bits )
    {
      std::ptrdiff_t i = std::countr_zero(bits);
      if( f(i / bits_per_element) ) { return true; }

      bits = bits & (bits - 1);
      if( bits_per_element == 2 ) bits = bits & (bits - 1);
    }
    return false;
  }
  else
  {
    std::ptrdiff_t offset = 0;
    while( bits )
    {
      std::ptrdiff_t count = std::countr_zero(bits);
      offset += count;
      if( f(offset / bits_per_element) ) { return true; }
      offset += bits_per_element;
      bits >>= count;
      bits >>= bits_per_element;
    }
    return false;
  }
}

template<callable_options O, typename L, typename F>
EVE_FORCEINLINE bool
iterate_selected_(EVE_REQUIRES(cpu_), O const& opts, L l, F&& f)
{
  auto ignore = opts[condition_key];
  if constexpr( std::same_as<L, bool> )
  {
    if( l && ignore.count(eve::as<eve::wide<int, eve::fixed<1>>> {}) )
    {
      return f(std::ptrdiff_t {0});
    }
    return false;
  }
  else if constexpr( L::size() == 1U ) { return iterate_selected[opts](l.get(0), f); }
  else if constexpr( logical_simd_value<L> )
  {
    return iterate_selected[ignore_none](top_bits {l, ignore}, f);
  }
  else if constexpr( !std::same_as<decltype(ignore), ignore_none_> )
  {
    return iterate_selected[ignore_none](l & L {ignore}, f);
  }
  else if constexpr( L::is_aggregated )
  {
    auto [lo, hi] = l.slice();
    if( iterate_selected(lo, f) ) { return true; }
    return iterate_selected(hi, plus_offset_lambda<F> {f, L::size() / 2});
  }
  else { return iterate_selected_int<L::bits_per_element>(l.as_int(), f); }
}
}
