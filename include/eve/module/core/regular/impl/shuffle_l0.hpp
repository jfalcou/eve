//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <algorithm>
#include <span>

#include <initializer_list>

namespace eve::detail::idx
{

constexpr bool
matches(const std::span<const std::ptrdiff_t> idxs, std::initializer_list<std::ptrdiff_t> pattern)
{
  if( idxs.size() != pattern.size() ) return false;

  auto pattern_f = pattern.begin();
  for( unsigned i = 0; i != idxs.size(); ++i )
  {
    if( idxs[i] == we_ ) continue;
    if( idxs[i] != pattern_f[i] ) return false;
  }

  return true;
}

// Can't variadic this
constexpr bool
matches(const std::span<const std::ptrdiff_t> idxs,
        std::initializer_list<std::ptrdiff_t> p1,
        std::initializer_list<std::ptrdiff_t> p2)
{
  return idx::matches(idxs, p1) || idx::matches(idxs, p2);
}

constexpr bool
is_identity(std::span<const std::ptrdiff_t> idxs)
{
  return idxs.size() == 1 && (idxs[0] == 0 || idxs[0] == we_);
}

constexpr bool
is_zero(std::span<const std::ptrdiff_t> idxs)
{
  return idxs.size() == 1 && idxs[0] == na_;
}

constexpr bool
has_zeroes(std::span<const std::ptrdiff_t> idxs)
{
  // std::any_of but in compile time that's not free.
  for( auto x : idxs )
  {
    if( x == na_ ) return true;
  }
  return false;
}

constexpr bool
are_below_ignoring_speicals(std::span<const std::ptrdiff_t> idxs, std::ptrdiff_t ub)
{
  // std::any_of but in compile time that's not free.
  for( auto x : idxs )
  {
    if( x == na_ || x == we_ ) continue;
    if( x >= ub ) return false;
  }
  return true;
}

constexpr bool
are_above_ignoring_speicals(std::span<const std::ptrdiff_t> idxs, std::ptrdiff_t lb)
{
  // std::any_of but in compile time that's not free.
  for( auto x : idxs )
  {
    if( x == na_ || x == we_ ) continue;
    if( x < lb ) return false;
  }
  return true;
}

constexpr bool
is_blend(std::span<const std::ptrdiff_t> idxs)
{
  std::ptrdiff_t s = std::ssize(idxs);
  if( s == 1 ) return false;

  // std::all_of
  for( int i = 0; i != s; ++i )
  {
    if( idxs[i] == na_ || idxs[i] == i || idxs[i] == i + s ) continue;
    return false;
  }
  return true;
}

template<std::size_t N>
constexpr auto
replace_we(std::span<const std::ptrdiff_t, N> idxs, std::ptrdiff_t with)
{
  std::array<std::ptrdiff_t, N> res = {};
  for( std::size_t i = 0; i != N; ++i ) { res[i] = idxs[i] == we_ ? with : idxs[i]; }
  return res;
}

} // namespace eve::detail::idx
