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

#include <eve/conditional.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <cstddef>
#include <random>
#include <string>
#include <type_traits>
#include <vector>

// Operations run over pre-computed lists of {ptr, ignore} cases, one per kind of ignore. Every case
// is drawn independently: first the ignore (uniformly), then a pointer valid for it (uniformly).
// The lists are long enough for the branch predictor not to learn them.
//
// op[ignore]         : the overall number, one operation of each kind per step
// op[ignore_first]...: each kind on its own
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

  template<typename T, std::ptrdiff_t N, typename Op>
  void memory_op_with_ignore_bench(std::string const& name, Op op)
  {
    using V = std::remove_const_t<T>;

    constexpr std::ptrdiff_t size = 4096 / sizeof(V);
    std::vector<V, eve::aligned_allocator<V, size>> buffer(size, V{1});

    T* begin = buffer.data();
    T* end   = begin + size;

    // Past what the branch predictor learns.
    constexpr std::size_t cases = 1 << 20;

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

    std::mt19937 g{42};
    auto fc = sample(firsts, cases, g);
    auto lc = sample(lasts, cases, g);
    auto ec = sample(extremas, cases, g);

    // Raw pointers captured by copy: doNotOptimizeAway clobbers memory, going through the vectors
    // would reload their data pointers on every operation.
    auto one = [&](auto const& list)
    {
      return [&, p = list.data()]
      {
        for( std::size_t i = 0; i < cases; ++i ) op(p + i);
      };
    };

    auto all = [&, f = fc.data(), l = lc.data(), e = ec.data()]
    {
      for( std::size_t i = 0; i < cases; ++i )
      {
        op(f + i);
        op(l + i);
        op(e + i);
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
