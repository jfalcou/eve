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

constexpr bool
has_zeroes(std::span<const std::ptrdiff_t> idxs)
{
  // std::any_of but in compile time that's not free.
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  while( f != l )
  {
    if( *f == na_ ) return true;
    ++f;
  }
  return false;
}

constexpr bool
is_all_zeroes(std::span<const std::ptrdiff_t> idxs)
{
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  while( f != l )
  {
    if( *f >= 0 ) return false;
    ++f;
  }
  return true;
}

constexpr bool
is_just_zeroes_replaced(std::span<const std::ptrdiff_t> idxs)
{
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  for( const auto *i = f; i != l; ++i )
  {
    if( *i == na_ || *i == we_ || *i == (i - f) ) continue;
    return false;
  }

  return true;
}

constexpr std::optional<std::ptrdiff_t>
is_just_setting_one_zero(std::span<const std::ptrdiff_t> idxs)
{
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  const std::ptrdiff_t *pos = nullptr;

  for( const auto *i = f; i != l; ++i )
  {
    if( *i == we_ || *i == (i - f) ) continue;
    if( *i == na_ )
    {
      if( pos ) return std::nullopt;
      pos = i;
      continue;
    }
    return std::nullopt;
  }

  if( !pos ) return std::nullopt;
  return pos - f;
}

constexpr std::optional<std::array<std::ptrdiff_t, 2>>
is_just_setting_one_lane(std::span<const std::ptrdiff_t> idxs)
{
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  const std::ptrdiff_t *pos = nullptr;

  for( const auto *i = f; i != l; ++i )
  {
    if( *i == we_ || *i == (i - f) ) continue;
    if( *i == na_ ) return std::nullopt;
    if( pos ) return std::nullopt;
    pos = i;
  }

  if( !pos ) return std::nullopt;
  return std::array {pos - f, *pos};
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

constexpr bool
shuffle_within_halves(std::span<const std::ptrdiff_t> idxs)
{
  const std::ptrdiff_t ssize = std::ssize(idxs);
  const std::ptrdiff_t half  = ssize / 2;

  if( ssize % 2 ) return false;

  for( std::ptrdiff_t i = 0; i != half; ++i )
  {
    if( idxs[i] >= half ) return false;
  }

  for( std::ptrdiff_t i = half; i != ssize; ++i )
  {
    if( 0 <= idxs[i] && idxs[i] < half ) return false;
  }

  return true;
}

template<std::size_t N>
constexpr auto
shuffle_halves_independetly(const std::array<std::ptrdiff_t, N>& p)
{
  auto lo = p;
  auto hi = p;

  for( std::size_t i = 0; i != N / 2; ++i )
  {
    if( p[i] == we_ ) hi[i] = we_;
    else hi[i] = (std::ptrdiff_t)i;
  }
  for( std::size_t i = N / 2; i != N; ++i )
  {
    if( p[i] == we_ ) lo[i] = we_;
    else lo[i] = (std::ptrdiff_t)i;
  }

  return std::array {lo, hi};
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

template<auto idxs>
constexpr auto
most_repeated_pattern_impl()
{
  if constexpr( constexpr auto p_half = idxm::is_repeating_pattern(idxs) )
  {
    return most_repeated_pattern_impl<*p_half>();
  }
  else return idxs;
}

template<std::ptrdiff_t... I>
constexpr auto most_repeated_pattern = most_repeated_pattern_impl<std::array {I...}>();

template<auto arr> constexpr auto most_repeated_pattern_a = most_repeated_pattern_impl<arr>();

template<std::size_t target, auto idxs>
constexpr auto
reduce_repeated_pattern_until_impl()
{
  if constexpr( idxs.size() <= target ) return idxs;
  else if constexpr( constexpr auto p_half = idxm::is_repeating_pattern(idxs) )
  {
    return reduce_repeated_pattern_until_impl<target, *p_half>();
  }
  else return idxs;
}

template<std::size_t target, std::ptrdiff_t... I>
constexpr auto reduce_repeated_pattern_until =
    reduce_repeated_pattern_until_impl<target, std::array {I...}>();

template<std::size_t target, std::ptrdiff_t... I>
constexpr auto repeated_pattern_of_size = []
{
  if constexpr( target == 0 ) return std::optional<std::array<std::ptrdiff_t, 1>> {};
  else
  {
    std::optional<std::array<std::ptrdiff_t, target>> res;
    constexpr auto repeated = idxm::reduce_repeated_pattern_until_impl<target, std::array {I...}>();
    if constexpr( repeated.size() == target ) { res = repeated; }
    return res;
  }
}();

template<std::size_t Times, std::size_t N>
constexpr std::array<std::ptrdiff_t, Times * N>
repeat(std::span<const std::ptrdiff_t, N> in)
{
  std::array<std::ptrdiff_t, Times * N> res = {};

  const auto *f = in.data();
  const auto *l = in.data() + in.size();

  std::ptrdiff_t *o   = res.data();
  std::ptrdiff_t *o_l = res.data() + res.size();

  std::ptrdiff_t offset = 0;

  while( o != o_l )
  {
    for( const auto *i = f; i != l; ++i )
    {
      *o = *i;
      if( *i >= 0 ) *o += offset;
      ++o;
    }
    offset += (std::ptrdiff_t)N;
  }

  return res;
}

template<std::size_t Times, std::size_t N>
constexpr auto
repeat(const std::array<std::ptrdiff_t, N>& in)
{
  return repeat<Times>(std::span<const std::ptrdiff_t, N>(in));
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

constexpr bool
is_in_order_from(std::span<const std::ptrdiff_t> idxs, std::ptrdiff_t from)
{
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();
  while( f != l )
  {
    if( *f != we_ && *f != from ) return false;
    ++from;
    ++f;
  }

  return true;
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

template<std::size_t N>
constexpr std::optional<std::array<std::array<std::ptrdiff_t, N>, 2>>
rotate_as_two_shifts_and_or(std::array<std::ptrdiff_t, N> idxs)
{
  if constexpr( N != 1 )
  {
    auto halve = is_repeating_pattern(idxs);
    if( halve )
    {
      auto r = rotate_as_two_shifts_and_or(*halve);
      if( !r ) return std::nullopt;
      auto [lo, hi] = *r;
      return std::array {repeat<2>(lo), repeat<2>(hi)};
    }
  }

  std::optional pos = is_rotate(idxs);
  if( !pos ) return std::nullopt;

  std::array<std::ptrdiff_t, N> shift_left  = idxs;
  std::array<std::ptrdiff_t, N> shift_right = idxs;

  std::size_t rotation_point = *pos;

  for( std::size_t i = 0; i != N; ++i )
  {
    if( idxs[i] == we_ ) continue;
    if( i < rotation_point ) shift_right[i] = na_;
    else shift_left[i] = na_;
  }

  return std::array {shift_left, shift_right};
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

template<std::size_t N>
constexpr auto
replace_na(std::span<const std::ptrdiff_t, N> idxs, std::ptrdiff_t with)
{
  std::array<std::ptrdiff_t, N> res = {};
  for( std::size_t i = 0; i != N; ++i ) { res[i] = idxs[i] == na_ ? with : idxs[i]; }
  return res;
}

template<std::size_t N>
constexpr auto
replace_na(const std::array<std::ptrdiff_t, N>& idxs, std::ptrdiff_t with)
{
  return replace_na(std::span<const std::ptrdiff_t, N>(idxs), with);
}

template<std::size_t N>
constexpr auto
just_second_shuffle(std::span<const std::ptrdiff_t, N> idxs, std::ptrdiff_t with)
{
  std::array<std::ptrdiff_t, N> res = {};

  auto s = (std::ptrdiff_t)N;

  for( std::size_t i = 0; i != N; ++i )
  {
    auto in = idxs[i];
    if( 0 <= in && in < s ) res[i] = with;
    else if( in < 0 ) res[i] = in;
    else res[i] = in - s;
  }
  return res;
}

template<std::size_t N>
constexpr auto
just_second_shuffle(const std::array<std::ptrdiff_t, N>& idxs, std::ptrdiff_t with)
{
  return just_second_shuffle(std::span<const std::ptrdiff_t, N>(idxs), with);
}

template<std::size_t N>
constexpr auto
just_first_shuffle(std::span<const std::ptrdiff_t, N> idxs, std::ptrdiff_t with)
{
  std::array<std::ptrdiff_t, N> res = {};

  auto s = (std::ptrdiff_t)N;

  for( std::size_t i = 0; i != N; ++i )
  {
    auto in = idxs[i];
    if( in >= s ) res[i] = with;
    else res[i] = in;
  }

  return res;
}

template<std::size_t N>
constexpr auto
just_first_shuffle(const std::array<std::ptrdiff_t, N>& idxs, std::ptrdiff_t with)
{
  return just_first_shuffle(std::span<const std::ptrdiff_t, N>(idxs), with);
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

  std::ptrdiff_t *o = res.data();

  for( auto idx : idxs )
  {
    for( int j = 0; j != G; ++j )
    {
      if( idx < 0 ) *o++ = idx;
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

constexpr std::span<const std::ptrdiff_t>
trim_trailing_we(std::span<const std::ptrdiff_t> idxs)
{
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  while( f != l )
  {
    if( *(l - 1) != we_ ) break;
    --l;
  }

  return {f, l};
}

constexpr std::optional<std::ptrdiff_t>
is_slide_left(std::span<const std::ptrdiff_t> idxs)
{
  // find(idxs, na_)
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  while( f != l )
  {
    if( *f == na_ ) break;
    ++f;
  }

  if( !is_all_zeroes(std::span(f, l)) ) return std::nullopt;

  std::span<const std::ptrdiff_t> remaining   = std::span(idxs.data(), f);
  auto                            first_index = is_in_order(remaining);
  if( !first_index ) return std::nullopt;

  // Can be bigger that std::ssize(idxs) if ordered chunk ends in we_
  if( *first_index + std::ssize(remaining) < std::ssize(idxs) ) return std::nullopt;
  return *first_index;
}

constexpr std::optional<std::ptrdiff_t>
is_slide_right(std::span<const std::ptrdiff_t> idxs)
{
  // find(reverse(idxs), na_)
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  const auto *m = l;

  while( true )
  {
    if( m == f ) break;
    --m;
    if( *m == na_ ) break;
  }

  if( !is_all_zeroes(std::span {f, m}) ) return std::nullopt;
  // unclear if this is correct but it doesn't matter
  if( m == l ) return std::ssize(idxs);

  if( *m == na_ ) { ++m; }
  f = m;

  //     [na_, na_, we_, 1]
  //  or [na_, we_,   0, 1]

  // tracing all we_.
  while( m != l )
  {
    if( *m != we_ ) break;
    ++m;
  }

  if( !is_in_order_from(std::span {m, l}, *m) ) return std::nullopt;

  // [na_, na_, we_, 2]
  if( *m > (m - f) ) return std::nullopt;

  return (m - idxs.data()) - *m;
}

constexpr bool
is_reverse(std::span<const std::ptrdiff_t> idxs)
{
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  while( f != l )
  {
    if( *f == we_ || *f == (l - f - 1) )
    {
      ++f;
      continue;
    }
    return false;
  }
  return true;
}

constexpr std::optional<std::ptrdiff_t>
is_lane_broadcast(std::span<const std::ptrdiff_t> idxs)
{
  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  while( f != l )
  {
    if( *f != we_ ) break;
    ++f;
  }

  if( f == l ) return std::nullopt;

  std::ptrdiff_t r = *f;
  ++f;

  while( f != l )
  {
    if( *f != we_ && *f != r ) return std::nullopt;
    ++f;
  }
  return r;
}

template<std::size_t G, std::size_t N>
constexpr auto
split_to_groups(std::span<const std::ptrdiff_t, N> idxs)
{
  static_assert(N % G == 0);

  using sub = std::array<std::ptrdiff_t, G>;

  std::array<sub, N / G> res = {};

  const auto *f = idxs.data();
  const auto *l = idxs.data() + idxs.size();

  auto *o = res.data();

  while( f != l )
  {
    std::copy_n(f, G, o->data());
    ++o;
    f += G;
  }

  return res;
}

template<std::size_t G, std::size_t N>
constexpr auto
split_to_groups(const std::array<std::ptrdiff_t, N>& idxs)
{
  return split_to_groups<G>(std::span<const std::ptrdiff_t, N>(idxs));
}

/*
 * First shuffle big groups, then shuffle withing groups
 *
 * Big big questions about the order of small/big shuffle
 * and when to do zeroes.
 * Case by case we'll see.
 */
template<std::size_t G, std::size_t N>
constexpr auto
put_bigger_groups_in_position(std::span<const std::ptrdiff_t, N> idxs)
{
  if constexpr( G == 0 || G > N )
  {
    return std::optional<
        kumi::tuple<std::array<std::ptrdiff_t, 1>, std::array<std::ptrdiff_t, N>>> {};
  }
  else
  {
    constexpr std::size_t group_count = (G == 0 || G >= N) ? 1 : N / G;

    using group_pattern_t   = std::array<std::ptrdiff_t, group_count>;
    using withing_pattern_t = std::array<std::ptrdiff_t, N>;

    std::optional<kumi::tuple<group_pattern_t, withing_pattern_t>> res;

    group_pattern_t   groups_pattern        = {};
    withing_pattern_t within_groups_pattern = {};

    for( std::size_t i = 0; i != group_count; ++i )
    {
      const std::size_t group_start = i * G;
      const std::size_t group_end   = (i + 1) * G;

      std::ptrdiff_t group_index = we_;
      for( std::size_t j = group_start; j != group_end; ++j )
      {
        if( idxs[j] < 0 )
        {
          group_index = std::max(idxs[j], group_index);
          continue;
        }
        std::ptrdiff_t cur = idxs[j] / G;
        if( cur == group_index || group_index < 0 )
        {
          group_index = cur;
          continue;
        }
        return res;
      }

      if( group_index < 0 )
      {
        groups_pattern[i] = we_;
        for( std::size_t j = group_start; j != group_end; ++j )
        {
          within_groups_pattern[j] = group_index;
        }
        continue;
      }

      groups_pattern[i] = group_index;

      for( std::size_t j = group_start; j != group_end; ++j )
      {
        if( idxs[j] < 0 )
        {
          within_groups_pattern[j] = idxs[j];
          continue;
        }
        within_groups_pattern[j] = idxs[j] % G + group_start;
      }
    }

    res = kumi::tuple {groups_pattern, within_groups_pattern};
    return res;
  }
}

template<std::size_t G, std::size_t N>
constexpr auto
put_bigger_groups_in_position(const std::array<std::ptrdiff_t, N>& idxs)
{
  return put_bigger_groups_in_position<G>(std::span<const std::ptrdiff_t, N>(idxs));
}

constexpr auto
add_shuffle_levels(std::span<const std::ptrdiff_t> ls)
{
  std::ptrdiff_t base      = 0;
  std::ptrdiff_t use_masks = 0;

  for( auto l : ls )
  {
    base += l & (~1);
    use_masks |= l & 1;
  }
  return base + use_masks;
}

constexpr auto
add_shuffle_levels(std::array<std::ptrdiff_t, 3> ls)
{
  return add_shuffle_levels(std::span(ls));
}

template<std::ptrdiff_t... ls>
constexpr auto
add_shuffle_levels(eve::index_t<ls>...)
{
  return index<add_shuffle_levels(std::array {ls...})>;
}

} // namespace eve::detail::idxm

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/shuffle_v2/simd/x86/idxm.hpp>
#endif
