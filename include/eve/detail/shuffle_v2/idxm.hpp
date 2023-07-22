//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/spec.hpp>
#include <eve/pattern.hpp>

#include <span>

/*
 * idxm => index math
 * algorithms for pattern index manipulations.
 * Mostly tested through shuffles.
 */

namespace eve::detail::idxm
{

constexpr bool
are_below_ignoring_specials(std::span<const std::ptrdiff_t> idxs, std::ptrdiff_t ub)
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
is_identity(std::span<const std::ptrdiff_t> idxs)
{
  return idxs.size() == 1 && (idxs[0] == 0 || idxs[0] == we_);
}

constexpr bool
is_zero(std::span<const std::ptrdiff_t> idxs)
{
  return idxs.size() == 1 && idxs[0] < 0;
}

template<auto arr>
constexpr auto
to_pattern()
{
  return []<std::size_t... i>(std::index_sequence<i...>)
  { return pattern<arr[i]...>; }(std::make_index_sequence<arr.size()> {});
}

template<std::size_t N>
constexpr auto
swap_xy(std::array<std::ptrdiff_t, N> in, std::ptrdiff_t s) -> std::array<std::ptrdiff_t, N>
{
  std::array<std::ptrdiff_t, N> swapped = in;

  for( auto& x : swapped )
  {
    if( x == na_ || x == we_ ) continue;
    if( x >= s ) x -= s;
    else x += s;
  }

  return swapped;
}

template<std::ptrdiff_t G, std::ptrdiff_t... I, typename T, typename... Ts>
constexpr bool
validate_pattern(eve::fixed<G>, pattern_t<I...>, eve::as<T>, eve::as<Ts>...)
{
  std::ptrdiff_t max_idx = T::size() * (sizeof...(Ts) + 1) / G;
  for( auto i : {I...} )
  {
    // we/na
    if( -2 <= i && i < max_idx ) continue;
    return false;
  }

  return true;
}

template<std::size_t Fundamental, std::size_t PatternSize>
constexpr auto
fix_indexes_to_fundamental(const std::array<std::ptrdiff_t, PatternSize>& p,
                           std::ptrdiff_t                                 cardinal)
{
  std::array<std::ptrdiff_t, std::max(PatternSize, Fundamental)> res {};
  std::size_t                                                    i = 0;

  std::ptrdiff_t wide_offest = (std::ptrdiff_t)Fundamental - cardinal;

  for( ; i != PatternSize; ++i )
  {
    std::ptrdiff_t x = p[i];
    if( x >= cardinal ) { x += wide_offest * (x / cardinal); }
    res[i] = x;
  }

  for( ; i != res.size(); ++i ) { res[i] = we_; }

  return res;
}

template<std::size_t N>
constexpr std::optional<std::array<std::ptrdiff_t, N / 2>>
is_repeating_pattern(const std::array<std::ptrdiff_t, N>& p)
{
  std::array<std::ptrdiff_t, N / 2> res = {};

  constexpr std::ptrdiff_t half = N / 2;
  for( std::size_t i = 0; i != N / 2; ++i )
  {
    std::ptrdiff_t x = p[i];
    std::ptrdiff_t y = p[i + (std::size_t)half];

    if( x >= half ) return std::nullopt;
    if( 0 <= y && y < half ) return std::nullopt;

    if( y > 0 ) y -= half;

    if( x == y || y == we_ )
    {
      res[i] = x;
      continue;
    }

    if( x == we_ )
    {
      res[i] = y;
      continue;
    }

    return std::nullopt;
  }

  return res;
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

// returns the starting index
constexpr std::optional<std::ptrdiff_t>
is_in_order(std::span<const std::ptrdiff_t> idxs)
{
  std::size_t i = 0, s = idxs.size();

  // find not we_ but in compile time that's not free
  while( true )
  {
    if( i == s ) return we_;
    if( idxs[i] != we_ ) break;
    ++i;
  }
  if( idxs[i] == na_ ) return std::nullopt;

  std::ptrdiff_t expected = idxs[i];
  std::ptrdiff_t from     = expected - (std::ptrdiff_t)i;

  // [we_, we_, 1] is not in order, for any we_.
  if( from < 0 ) return std::nullopt;

  while( true )
  {
    ++i;
    ++expected;
    if( i == s ) return from;
    if( idxs[i] == we_ ) continue;
    if( idxs[i] != expected ) return std::nullopt;
  }
}

constexpr std::optional<std::ptrdiff_t>
is_rotate(std::span<const std::ptrdiff_t> idxs)
{
  if( idxs.empty() ) { return 0; }

  auto point = std::min_element(idxs.begin(),
                                idxs.end(),
                                [](auto x, auto y)
                                {
                                  // we_ should be not prefered
                                  // na_ means not a rotate, but we will detect it later
                                  return (unsigned)x < (unsigned)y;
                                });

  // all are we_
  if( *point == we_ ) return 0;

  // find where 0 is. We can be to the left or to the right.
  if( *point <= point - idxs.begin() )
  {
    // [3, we_, |1, 2] => [3, | we_, 1, 2]
    point -= *point;
  }
  else
  {
    // [|1, 2, 3, we_] => [1, 2, 3, | we_]
    point += idxs.size() - *point;
  }

  std::ptrdiff_t rotation = point - idxs.begin();

  // these filter out na_
  auto rhs_start = is_in_order({point, idxs.end()});
  if( rhs_start != 0 && rhs_start != we_ ) return std::nullopt;

  auto lhs_start = is_in_order({idxs.begin(), point});
  if( lhs_start != (idxs.size() - rotation) && lhs_start != we_ ) return std::nullopt;

  return rotation;
}

template<std::ptrdiff_t Part, std::ptrdiff_t... I>
constexpr auto
slice_pattern(pattern_t<I...>)
{
  constexpr std::array idxs {I...};
  if constexpr( Part >= idxs.size() ) return kumi::tuple {pattern<I...>};
  else
  {
    constexpr auto sliced_array = [&]
    {
      using part_t = std::array<std::ptrdiff_t, (std::size_t)Part>;

      std::array<part_t, idxs.size() / Part> res = {};

      const std::ptrdiff_t *in = idxs.data();
      for( auto& part : res )
      {
        std::copy_n(in, Part, part.data());
        in += Part;
      }

      return res;
    }();

    return [&]<std::size_t... i>(std::index_sequence<i...>) {
      return kumi::tuple {to_pattern<sliced_array[i]>()...};
    }(std::make_index_sequence<sizeof...(I) / Part> {});
  }
}

template<std::ptrdiff_t Cardinal, std::ptrdiff_t... I>
constexpr auto
drop_unused_wides(eve::pattern_t<I...>)
{
  constexpr std::size_t kSizeNeeded = std::max(std::ptrdiff_t {1}, std::max({I...}) / Cardinal + 1);

  constexpr auto used_buffer_size = [&]
  {
    std::array<char, kSizeNeeded> register_used = {};
    for( auto i : {I...} )
    {
      if( i < 0 ) continue;
      register_used[i / Cardinal] = 1;
    }
    std::array<int, kSizeNeeded> r   = {};
    int                         *out = r.data();
    for( std::size_t i = 0; i != kSizeNeeded; ++i )
    {
      if( register_used[i] ) { *out++ = (int)i; }
    }

    // no registers means one register.
    if( out == r.data() ) ++out;

    return std::pair {r, (std::size_t)(out - r.data())};
  }();

  constexpr auto used_wide_indexes = [&]
  {
    std::array<int, used_buffer_size.second> r = {};
    std::copy_n(used_buffer_size.first.data(), used_buffer_size.second, r.data());
    return r;
  }();

  constexpr auto new_pattern_array = [&]
  {
    std::array<int, kSizeNeeded> reduce_offset_by = {};

    for( int new_wide_idx = 0; int wide_idx : used_wide_indexes )
    {
      reduce_offset_by[(std::size_t)wide_idx] = (wide_idx - new_wide_idx) * Cardinal;
      ++new_wide_idx;
    }

    std::array res = {I...};

    for( auto& i : res )
    {
      if( i < 0 ) continue;
      int wide_idx = i / Cardinal;
      i -= reduce_offset_by[(std::size_t)wide_idx];
    }

    return res;
  }();

  return kumi::tuple {to_pattern<new_pattern_array>(), used_wide_indexes};
}

constexpr bool
matches(const std::span<const std::ptrdiff_t> idxs, std::initializer_list<std::ptrdiff_t> pattern)
{
  if( idxs.size() != pattern.size() ) return false;

  auto pattern_f = pattern.begin();
  for( unsigned i = 0; i != idxs.size(); ++i )
  {
    if( idxs[i] == we_ || pattern_f[i] == we_ ) continue;
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
  return idxm::matches(idxs, p1) || idxm::matches(idxs, p2);
}

template<std::size_t N>
constexpr auto
replace_we(std::span<const std::ptrdiff_t, N> idxs, std::ptrdiff_t with)
{
  std::array<std::ptrdiff_t, N> res = {};
  for( std::size_t i = 0; i != N; ++i ) { res[i] = idxs[i] == we_ ? with : idxs[i]; }
  return res;
}

template<std::size_t N>
constexpr auto
replace_we(const std::array<std::ptrdiff_t, N>& idxs, std::ptrdiff_t with)
{
  return replace_we(std::span<const std::ptrdiff_t, N>(idxs), with);
}

constexpr bool
is_blend(std::span<const std::ptrdiff_t> idxs, std::ptrdiff_t cardinal)
{
  std::ptrdiff_t s = std::ssize(idxs);
  if( s == 1 || s != cardinal ) return false;

  // std::all_of
  for( int i = 0; i != s; ++i )
  {
    if( idxs[i] == we_ || idxs[i] == i || idxs[i] == i + s ) continue;
    return false;
  }
  return true;
}

template<std::ptrdiff_t G, std::size_t N>
constexpr std::array<std::ptrdiff_t, N * G>
expand_group(std::span<const std::ptrdiff_t, N> idxs)
{
  std::array<std::ptrdiff_t, N * G> res = {};

  std::ptrdiff_t* o = res.data();

  for (auto idx : idxs) {
    for (int j = 0; j != G; ++j) {
      if (idx < 0) *o++ = idx;
      else *o++ = idx * G + j;
    }
  }

  return res;
}

template<std::ptrdiff_t G, std::size_t N>
constexpr std::array<std::ptrdiff_t, N * G>
expand_group(std::array<std::ptrdiff_t, N> idxs)
{
  return expand_group<G>(std::span<const std::ptrdiff_t, N>(idxs));
}

} // namespace eve::detail::idxm

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/shuffle_v2/simd/x86/idxm.hpp>
#endif
