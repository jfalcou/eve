//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include "unit/module/algo/algo_test.hpp"

#include <algorithm>
#include <numeric>
#include <vector>

namespace algo_test
{

// produces test cases with up to 64 numbers in each array
struct set_intersect_test_case_gen
{
  std::vector<std::int8_t> a;
  std::vector<std::int8_t> b;
  std::vector<std::int8_t> c;

  void fill_vec(std::uint64_t m, std::vector<std::int8_t>& vec)
  {
    vec.resize((unsigned)std::popcount(m));

    auto o = vec.begin();
    for( unsigned i = 0; i != 64; ++i )
    {
      if( m & (std::uint64_t {1} << i) ) *o++ = (std::int8_t)i;
    }
  }

  void make_test(std::uint64_t selected_a, std::uint64_t selected_b)
  {
    fill_vec(selected_a, a);
    fill_vec(selected_b, b);
    fill_vec(selected_a & selected_b, c);
  }
};

inline const std::vector<std::pair<std::uint64_t, std::uint64_t>>&
set_intersect_test_cases()
{
  static const auto r = []
  {
    std::vector<std::pair<std::uint64_t, std::uint64_t>> res;
    std::mt19937                                         gen {0};
    std::uniform_int_distribution<std::uint64_t>         dis;

    for( std::size_t i = 0; i != 16; ++i )
    {
      for( std::size_t j = 0; j != 16; ++j ) { res.emplace_back(i, j); }
    }

    for( std::size_t i = 0; i != 10'000; ++i ) { res.emplace_back(dis(gen), dis(gen)); }

    return res;
  }();

  return r;
}

// No alignment and such tests
template<typename T, typename Algo>
void
set_intersection_test_values(eve::as<T>, Algo algo)
{
  set_intersect_test_case_gen test_case_gen;

  std::vector<eve::element_type_t<T>> a, b, c, expected;
  std::vector<eve::element_type_t<T>> smaller, expected_smaller;

  auto smaller_c_test = [&](std::size_t c_size_offset)
  {
    if( c_size_offset >= c.size() ) return;
    smaller.resize(c.size() - c_size_offset);
    expected_smaller.assign(expected.begin(), expected.begin() + std::ssize(smaller));

    auto [fa, fb, fc] = algo(a, b, smaller);
    TTS_EQUAL(smaller, expected_smaller);

    if( a.empty() || b.empty() )
    {
      TTS_EQUAL(fa, a.end());
      TTS_EQUAL(fb, b.end());
      TTS_EQUAL(fc, smaller.begin());
      return;
    }

    TTS_EQUAL(fc, smaller.end());

    if( smaller.empty() )
    {
      TTS_EQUAL(fa, a.begin());
      TTS_EQUAL(fb, b.begin());
      return;
    }

    if( fa == a.end() || fb == b.end() )
    {
      TTS_EQUAL(fa, a.end());
      TTS_EQUAL(fb, b.end());
      return;
    }

    TTS_EQUAL(*(fa - 1), *(fb - 1));
    TTS_EQUAL(*(fa - 1), *(fc - 1));

    if( *(fa - 1) != *(fb - 1) )
    {
      std::cerr << "a: " << tts::as_string(a) << "\nb: " << tts::as_string(b)
                << "\nc: " << tts::as_string(smaller) << std::endl;
      std::cerr << "fa: " << fa - a.begin() << " fb: " << fb - b.begin() << std::endl;
      std::terminate();
    }
  };

  for( const auto& tc : set_intersect_test_cases() )
  {
    test_case_gen.make_test(tc.first, tc.second);
    a.assign(test_case_gen.a.begin(), test_case_gen.a.end());
    b.assign(test_case_gen.b.begin(), test_case_gen.b.end());
    c.resize(test_case_gen.c.size() + 1);

    expected.assign(test_case_gen.c.begin(), test_case_gen.c.end());
    auto [fa, fb, fc] = algo(a, b, c);

    TTS_EQUAL(a.end() - fa, 0) << "a: " << tts::as_string(a) << "\nb: " << tts::as_string(b);
    TTS_EQUAL(b.end() - fb, 0) << "a: " << tts::as_string(a) << "\nb: " << tts::as_string(b);
    TTS_EQUAL(c.end() - fc, 1) << "a: " << tts::as_string(a) << "\nb: " << tts::as_string(b);
    c.erase(fc, c.end());

    TTS_EQUAL(expected, c) << "a: " << tts::as_string(a) << "\nb: " << tts::as_string(b);

    smaller_c_test(1u);
    smaller_c_test(2u);
    smaller_c_test(5u);
    smaller_c_test(c.size() - 1);
    smaller_c_test(c.size());
  }
}

// We at most iterate one of the ranges as simd from different offsets,
// so that's the only case that is concerning.
template<typename Algo> struct set_intersect_ptr_test
{
  Algo alg;

  explicit set_intersect_ptr_test(Algo alg) : alg(alg) {}

  void init(auto *, auto *f, auto *l, auto *) const { std::iota(f, l, 0); }

  // intersecting with one value should be enough
  auto run(auto&& rng) const
  {
    auto f  = eve::unalign(rng.begin());
    auto l  = eve::unalign(rng.end());
    using T = decltype(eve::read(f));

    std::vector<T> intersect_with;
    std::vector<T> expected;
    if( f != l )
    {
      if( *f > 0 ) { intersect_with.push_back(*f - 1); }
      intersect_with.push_back(*f);
      expected.push_back(*f);
      intersect_with.push_back(*f + 2);
      if( l - f > 2 ) { expected.push_back(*f + 2); }
    }

    {
      std::vector<T> actual(4, 0);
      actual.erase(alg(rng, intersect_with, actual).out, actual.end());
      TTS_EQUAL(expected, actual);
    }

    {
      std::vector<T> actual(4, 0);
      actual.erase(alg(intersect_with, rng, actual).out, actual.end());
      TTS_EQUAL(expected, actual);
    }
  }

  void adjust(auto *, auto *, auto *, auto *) const {}
};

template<typename T, typename Algo>
void
set_intersection_test_position(eve::as<T> tgt, Algo alg)
{
  algo_test::page_ends_test(tgt, set_intersect_ptr_test {alg});
}

template<typename T, typename Algo>
void
set_intersection_test_duplicates(eve::as<T>, Algo alg)
{
  // Checking that the algorithm finishes
  std::vector<eve::element_type_t<T>> a, b, c;
  a.resize(256, 1);
  b.resize(256, 1);
  c.resize(256, 1);

  for (std::size_t s1 = 0; s1 != 150; ++s1) {
    for (std::size_t s2 = 0; s2 != 150; ++s2) {
      std::span a_span{a.data(), s1};
      std::span b_span{b.data(), s2};
      alg(a_span, b_span, c);
    }
  }

}


template<typename T, typename Algo>
void
set_intersection_test(eve::as<T> tgt, Algo alg)
{
  set_intersection_test_values(tgt, alg);
  set_intersection_test_position(tgt, alg);
  set_intersection_test_duplicates(tgt, alg);
}

}
