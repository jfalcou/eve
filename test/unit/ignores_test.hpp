//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include "test.hpp"
#include <eve/module/core.hpp>

#include <algorithm>
#include <vector>

//==================================================================================================
// test_ignores_for<N>(f) calls f(ignore) for relative conditionals of every type over N lanes, and
// again wrapped in eve::never_empty for the ones keeping a lane.
//
// Up to exhaustive_ignores_limit lanes, every count is tried. Above, the edges and the middle of the
// register, plus random_counts random ones. Counts are sorted, duplicates are fine.
//==================================================================================================
namespace ignores_test
{
  inline constexpr std::ptrdiff_t exhaustive_ignores_limit = 16;
  inline constexpr int            random_counts            = 24;

  template<std::ptrdiff_t N> std::vector<std::ptrdiff_t> counts()
  {
    std::vector<std::ptrdiff_t> ks;

    if constexpr( N <= exhaustive_ignores_limit )
    {
      for( std::ptrdiff_t k = 0; k <= N; ++k ) ks.push_back(k);
    }
    else
    {
      ks = {0, 1, 2, N / 2 - 1, N / 2, N / 2 + 1, N - 2, N - 1, N};
      for( int i = 0; i != random_counts; ++i ) ks.push_back(tts::random_value<std::ptrdiff_t>(0, N));
      std::sort(ks.begin(), ks.end());
    }

    return ks;
  }

  template<typename F, typename C> void run(F& f, C c)
  {
    constexpr bool wrapped = !std::same_as<C, decltype(eve::drop_never_empty(c))>;
    eve::test::scoped_context ctx {"ignore: ", wrapped ? "never_empty " : "", c};
    f(c);
  }
}

// Counts never exceed N: keep_between(a, b) needs a <= b and ignore_extrema(a, b) needs a + b <= N.
template<std::ptrdiff_t N, typename F> void test_ignores_for(F f)
{
  ignores_test::run(f, eve::ignore_none);
  ignores_test::run(f, eve::never_empty {eve::ignore_none});
  ignores_test::run(f, eve::ignore_all);

  auto const ks = ignores_test::counts<N>();

  for( auto k : ks )
  {
    ignores_test::run(f, eve::keep_first(k));
    ignores_test::run(f, eve::keep_last(k));
    ignores_test::run(f, eve::ignore_first(k));
    ignores_test::run(f, eve::ignore_last(k));

    if( k != 0 )
    {
      ignores_test::run(f, eve::never_empty {eve::keep_first(k)});
      ignores_test::run(f, eve::never_empty {eve::keep_last(k)});
    }

    if( k != N )
    {
      ignores_test::run(f, eve::never_empty {eve::ignore_first(k)});
      ignores_test::run(f, eve::never_empty {eve::ignore_last(k)});
    }
  }

  for( std::size_t i = 0; i != ks.size(); ++i )
  {
    for( std::size_t j = i; j != ks.size(); ++j )
    {
      ignores_test::run(f, eve::keep_between(ks[i], ks[j]));
      if( ks[i] != ks[j] ) ignores_test::run(f, eve::never_empty {eve::keep_between(ks[i], ks[j])});
    }

    for( std::size_t j = 0; j != ks.size() && ks[i] + ks[j] <= N; ++j )
    {
      ignores_test::run(f, eve::ignore_extrema(ks[i], ks[j]));
      if( ks[i] + ks[j] != N ) ignores_test::run(f, eve::never_empty {eve::ignore_extrema(ks[i], ks[j])});
    }
  }
}
