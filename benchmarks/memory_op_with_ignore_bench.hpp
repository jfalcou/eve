//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#ifndef BENCHMARKS_MEMORY_OP_WITH_IGNORE_BENCH_HPP
#define BENCHMARKS_MEMORY_OP_WITH_IGNORE_BENCH_HPP

#include "nanobench.h"
#include "unit/memory/page.hpp"

#include <eve/as.hpp>
#include <eve/conditional.hpp>
#include <eve/traits/element_type.hpp>
#include <cstddef>
#include <random>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

// Benchmarks a memory op on ptr + ignore, with pointers both inside a page and across its ends.
namespace eve::bench
{
  template<typename T, typename C> struct ignore_case
  {
    T*  ptr;
    C   ignore;
  };

  // This is not std::sample, because we want to select more elements out than there were on the
  // input. And repeating elements are fine.
  template<typename T, typename C>
  auto sample(std::vector<std::vector<ignore_case<T, C>>> const& groups, std::size_t n, std::mt19937& g)
  {
    std::uniform_int_distribution<std::size_t> pick_group(0, groups.size() - 1);

    std::vector<ignore_case<T, C>> res;
    res.reserve(n);
    while( res.size() < n )
    {
      auto const& group = groups[pick_group(g)];
      res.push_back(group[std::uniform_int_distribution<std::size_t>(0, group.size() - 1)(g)]);
    }
    return res;
  }

  template<typename T, typename W>
  auto ignore_case_groups(T* begin, T* end, eve::as<W>)
  {
    constexpr std::ptrdiff_t N = W::size();

    std::vector<T*> inside;
    for( std::ptrdiff_t i = 0; i < N; ++i )
    {
      inside.push_back(begin + i);
      inside.push_back(end - N - i);
    }

    std::vector<std::vector<ignore_case<T, eve::ignore_first>>>   firsts;
    std::vector<std::vector<ignore_case<T, eve::ignore_last>>>    lasts;
    std::vector<std::vector<ignore_case<T, eve::ignore_extrema>>> extremas;

    for( std::ptrdiff_t k = 0; k < N; ++k )
    {
      auto& f = firsts.emplace_back();
      auto& l = lasts.emplace_back();

      for( auto p : inside )
      {
        f.push_back({p, eve::ignore_first(k)});
        l.push_back({p, eve::ignore_last(k)});
      }

      for( std::ptrdiff_t j = 1; j <= k; ++j )
      {
        f.push_back({begin - j, eve::ignore_first(k)});
        l.push_back({end - N + j, eve::ignore_last(k)});
      }
    }

    for( std::ptrdiff_t f = 0; f < N; ++f )
    {
      for( std::ptrdiff_t l = 0; f + l < N; ++l )
      {
        auto& e = extremas.emplace_back();
        for( auto p : inside ) e.push_back({p, eve::ignore_extrema(f, l)});
        for( std::ptrdiff_t j = 1; j <= f; ++j ) e.push_back({begin - j, eve::ignore_extrema(f, l)});
        for( std::ptrdiff_t j = 1; j <= l; ++j ) e.push_back({end - N + j, eve::ignore_extrema(f, l)});
      }
    }

    return std::tuple{std::move(firsts), std::move(lasts), std::move(extremas)};
  }

  template<typename W, typename Op>
  void memory_op_with_ignore_bench(std::string const& name, eve::as<W> tgt, Op op)
  {
    using T = eve::element_type_t<W>;

    guarded_test_page<T> page;

    T* begin = page.data();
    T* end   = begin + page.size();

    constexpr std::size_t cases = 1 << 20;

    auto [firsts, lasts, extremas] = ignore_case_groups(begin, end, tgt);

    std::mt19937 g{42};
    auto fc = sample(firsts, cases, g);
    auto lc = sample(lasts, cases, g);
    auto ec = sample(extremas, cases, g);

    // NOTE: we were considering benchmarking latency instead of
    // throughput for these ops but most of the time CPU can execute
    // the following code while load/store is happening, so that idea
    // was dismissed.

    auto one = [&](auto const& list)
    {
      return [&, p = list.data()]
      {
        for( std::size_t i = 0; i < cases; ++i ) op(p[i].ptr, p[i].ignore);
      };
    };

    auto all = [&, f = fc.data(), l = lc.data(), e = ec.data()]
    {
      for( std::size_t i = 0; i < cases; ++i )
      {
        op(f[i].ptr, f[i].ignore);
        op(l[i].ptr, l[i].ignore);
        op(e[i].ptr, e[i].ignore);
      }
    };

    ankerl::nanobench::Bench b;
    b.unit(name).minEpochIterations(10).performanceCounters(true);

    b.batch(3 * cases).run(name + "[ignore]", all);
    b.batch(cases).run(name + "[ignore_first]", one(fc));
    b.batch(cases).run(name + "[ignore_last]", one(lc));
    b.batch(cases).run(name + "[ignore_extrema]", one(ec));
  }
}

#endif
