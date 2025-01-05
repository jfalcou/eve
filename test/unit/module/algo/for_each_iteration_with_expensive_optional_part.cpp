//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include <cstdint>
#include <vector>

namespace
{

constexpr std::size_t kMaxTestDataSize = 100;

struct fixture
{
  fixture()
  {
    data.fill(0);
    data[0] = data[1] = data[2] = data[3] = '_';
  }

  auto aligned_begin()
  {
    using ap = eve::aligned_ptr<char, eve::fixed<4>>;
    return eve::algo::ptr_iterator<ap, eve::fixed<4>> {ap(data.begin())};
  }

  auto aligned_end() { return aligned_begin() + data.size(); }

  auto unaligned_begin() { return eve::unalign(aligned_begin()); }
  auto unaligned_end() { return eve::unalign(aligned_end()); }

  std::string_view res() { return data.data(); }

  alignas(64) std::array<char, kMaxTestDataSize> data;
};

struct test_delegate
{
  char                       *data;
  std::vector<std::ptrdiff_t> where_to_expensive;
  std::ptrdiff_t              expensive_returns_true_at;

  std::ptrdiff_t where_to_expensive_pos = 0;
  std::ptrdiff_t expensive_offset       = 0;

  test_delegate(char                       *_data,
                std::vector<std::ptrdiff_t> _where_to_expensive,
                std::ptrdiff_t              _expensive_returns_true_at = -1)
      : data(_data)
      , where_to_expensive(std::move(_where_to_expensive))
      , expensive_returns_true_at(_expensive_returns_true_at)
  {}

  bool step(auto it, auto ignore)
  {
    auto  tgt = eve::as<eve::wide<std::int8_t, eve::fixed<4>>> {};
    char *ptr = it.ptr;

    std::ptrdiff_t it_idx = it.ptr - data;
    TTS_LESS_EQUAL(it_idx, (std::ptrdiff_t)kMaxTestDataSize, REQUIRED) << "sanity check";

    for( std::ptrdiff_t i = ignore.offset(tgt); i; --i ) { *ptr++ = 'i'; }
    for( std::ptrdiff_t i = ignore.count(tgt); i; --i )
    {
      TTS_EXPECT(*ptr == 0 || *ptr == '_')
          << "repeated processing: " << *ptr << " ptr - data: " << (ptr - data);
      *ptr++ = 'a';
    }
    for( std::ptrdiff_t i = ignore.roffset(tgt); i; --i ) { *ptr++ = 'i'; }

    if( where_to_expensive_pos < std::ssize(where_to_expensive) )
    {
      auto next_expensive = where_to_expensive[where_to_expensive_pos];

      if( it_idx <= next_expensive && next_expensive < it_idx + 4 )
      {
        expensive_offset = next_expensive - it_idx;
        return true;
      }
    }

    return false;
  }

  bool expensive_part(auto base_expensive)
  {
    std::ptrdiff_t it_idx         = base_expensive.ptr - data;
    std::ptrdiff_t interupted_for = it_idx + expensive_offset;

    TTS_EQUAL(interupted_for, where_to_expensive[where_to_expensive_pos]);

    do {
      auto next_expensive = where_to_expensive[where_to_expensive_pos];

      if( next_expensive >= it_idx + 4 ) { break; }

      TTS_EQUAL(data[next_expensive], 'a');
      data[next_expensive] = 'e';

      if( next_expensive == expensive_returns_true_at ) { return true; }

      ++where_to_expensive_pos;
    }
    while( where_to_expensive_pos < std::ssize(where_to_expensive) );

    return false;
  }
};

template<bool align, int unroll> struct run_test_impl
{
  int                         offset;
  int                         size;
  std::vector<std::ptrdiff_t> where_to_expensive;
  int                         expensive_returns_true_at;

  template<bool divisible> std::string run_impl(auto& fix, auto f, auto l)
  {
    test_delegate d {fix.data.data(), where_to_expensive, expensive_returns_true_at};

    auto iter = eve::algo::for_each_iteration_with_expensive_optional_part(
        []
        {
          if constexpr( align && !divisible )
          {
            return eve::algo::traits {eve::algo::unroll<unroll>};
          }
          else if constexpr( align && divisible )
          {
            return eve::algo::traits {eve::algo::divisible_by_cardinal, eve::algo::unroll<unroll>};
          }
          else if constexpr( !align && !divisible )
          {
            return eve::algo::traits {eve::algo::no_aligning, eve::algo::unroll<unroll>};
          }
          else if constexpr( !align && divisible )
          {
            return eve::algo::traits {eve::algo::no_aligning,
                                      eve::algo::divisible_by_cardinal,
                                      eve::algo::unroll<unroll>};
          }
        }(),
        f,
        l);
    iter(d);
    return std::string(fix.res());
  }

  std::string operator()()
  {
    std::string res;
    {
      fixture fix;
      auto    f = fix.unaligned_begin() + offset;
      auto    l = f + size;
      res       = run_impl<false>(fix, f, l);
    }

    // just aligned
    if( offset % 4 == 0 )
    {
      std::string res1;
      fixture     fix;
      auto        f = fix.aligned_begin() + offset;
      auto        l = eve::unalign(f) + size;
      res1          = run_impl<false>(fix, f, l);
      TTS_EQUAL(res, res1);
    }

    // just divisible
    if( size % 4 == 0 )
    {
      std::string res1;
      fixture     fix;
      auto        f = fix.unaligned_begin() + offset;
      auto        l = eve::unalign(f) + size;
      res1          = run_impl<true>(fix, f, l);
      TTS_EQUAL(res, res1);
    }

    // 1. align/unaling divisible
    if( offset % 4 == 0 && size % 4 == 0 )
    {
      std::string res1;
      fixture     fix;
      auto        f = fix.aligned_begin() + offset;
      auto        l = eve::unalign(f) + size;
      res1          = run_impl<true>(fix, f, l);
      TTS_EQUAL(res, res1);
    }

    // 2. aligned both ends
    if( offset % 4 == 0 && size % 4 == 0 )
    {
      std::string res1;
      fixture     fix;
      auto        f = fix.aligned_begin() + offset;
      auto        l = f + size;
      res1          = run_impl<true>(fix, f, l);
      TTS_EQUAL(res, res1);
    }

    return res;
  }
};

template<bool align>
std::string
run_test(int                         offset,
         int                         size,
         std::vector<std::ptrdiff_t> where_to_expensive        = {},
         int                         expensive_returns_true_at = -1)
{
  std::string unroll1 =
      run_test_impl<align, 1> {offset, size, where_to_expensive, expensive_returns_true_at}();

  std::string unroll2 =
      run_test_impl<align, 2> {offset, size, where_to_expensive, expensive_returns_true_at}();

  std::string unroll4 =
      run_test_impl<align, 4> {offset, size, where_to_expensive, expensive_returns_true_at}();

  TTS_EQUAL(unroll1, unroll2);
  TTS_EQUAL(unroll1, unroll4);
  return unroll1;
}

} // namespace

TTS_CASE("eve.algo.for_each_iteration_with_expensive_optional_part, aligning, no matches")
{
  TTS_EQUAL(run_test<true>(0, 1), "aiii");
  TTS_EQUAL(run_test<true>(0, 2), "aaii");
  TTS_EQUAL(run_test<true>(1, 1), "iaii");
  TTS_EQUAL(run_test<true>(1, 2), "iaai");
  TTS_EQUAL(run_test<true>(1, 3), "iaaa");

  TTS_EQUAL(run_test<true>(0, 8),
            "aaaa"
            "aaaa");

  TTS_EQUAL(run_test<true>(1, 14),
            "iaaa"
            "aaaa"
            "aaaa"
            "aaai");
};

TTS_CASE("eve.algo.for_each_iteration_with_expensive_optional_part, no aligning, no matches")
{
  TTS_EQUAL(run_test<false>(0, 1), "aiii");
  TTS_EQUAL(run_test<false>(0, 2), "aaii");
  TTS_EQUAL(run_test<false>(1, 1), "_aiii");
  TTS_EQUAL(run_test<false>(1, 2), "_aaii");
  TTS_EQUAL(run_test<false>(1, 3), "_aaai");

  TTS_EQUAL(run_test<false>(0, 8),
            "aaaa"
            "aaaa");

  TTS_EQUAL(run_test<false>(1, 8),
            "_"
            "aaaa"
            "aaaa");

  TTS_EQUAL(run_test<false>(1, 14),
            "_"
            "aaaa"
            "aaaa"
            "aaaa"
            "aaii");
};

TTS_CASE("eve.algo.for_each_iteration_with_expensive_optional_part, aligning, some expensive")
{
  TTS_EQUAL(run_test<true>(0,
                           1,
                           /*where to expensive*/ {0}),
            "eiii");
  TTS_EQUAL(run_test<true>(0,
                           4,
                           /*where to expensive*/ {0, 1, 2, 3}),
            "eeee");
  TTS_EQUAL(run_test<true>(0,
                           5,
                           /*where to expensive*/ {0, 1, 2, 3}),
            "eeeeaiii");
  TTS_EQUAL(run_test<true>(1,
                           5,
                           /*where to expensive*/ {1}),
            "ieaaaaii");
  TTS_EQUAL(run_test<true>(1,
                           5,
                           /*where to expensive*/ {2, 3}),
            "iaeeaaii");
  TTS_EQUAL(run_test<true>(1,
                           5,
                           /*where to expensive*/ {2, 5}),
            "iaeaaeii");

  TTS_EQUAL(run_test<true>(1,
                           22,
                           /*where to expensive*/
                           {
                               // clang-format off
                               1, 2, 3, 4,
                               5, 6, 7, 8,
                               9, 10, 11, 12,
                               13, 14, 15, 16,
                               17, 18, 19, 20,
                               21, 22
                               // clang-format on
                           }),
            "ieee"
            "eeee"
            "eeee"
            "eeee"
            "eeee"
            "eeei");
};

TTS_CASE("eve.algo.for_each_iteration_with_expensive_optional_part, no aligning, some expensive")
{
  TTS_EQUAL(run_test<false>(0,
                            1,
                            /*where to expensive*/ {0}),
            "eiii");
  TTS_EQUAL(run_test<false>(0,
                            4,
                            /*where to expensive*/ {0, 1, 2, 3}),
            "eeee");
  TTS_EQUAL(run_test<false>(0,
                            5,
                            /*where to expensive*/ {0, 1, 2, 3}),
            "eeeeaiii");
  TTS_EQUAL(run_test<false>(1,
                            5,
                            /*where to expensive*/ {1}),
            "_eaaaaiii");
  TTS_EQUAL(run_test<false>(1,
                            5,
                            /*where to expensive*/ {2, 3}),
            "_aeeaaiii");
  TTS_EQUAL(run_test<false>(1,
                            5,
                            /*where to expensive*/ {2, 5}),
            "_aeaaeiii");
  TTS_EQUAL(run_test<false>(1,
                            22,
                            /*where to expensive*/
                            {
                                // clang-format off
                               1, 2, 3, 4,
                               5, 6, 7, 8,
                               9, 10, 11, 12,
                               13, 14, 15, 16,
                               17, 18, 19, 20,
                               21, 22
                                // clang-format on
                            }),
            "_eee"
            "eeee"
            "eeee"
            "eeee"
            "eeee"
            "eeei"
            "i");
};

TTS_CASE("eve.algo.for_each_iteration_with_expensive_optional_part, some expensive, stop check")
{
  TTS_EQUAL(run_test<true>(0,
                           5,
                           /*where to expensive*/ {0, 1, 2, 3},
                           /*stop at*/ 2),
            "eeea");

  TTS_EQUAL(run_test<false>(0,
                           5,
                           /*where to expensive*/ {0, 1, 2, 3},
                           /*stop at*/ 2),
            "eeea");
  TTS_EQUAL(run_test<true>(1,
                           5,
                           /*where to expensive*/ {1},
                           /*stop at*/ 1),
            "ieaa");
  TTS_EQUAL(run_test<false>(1,
                           5,
                           /*where to expensive*/ {1},
                           /*stop at*/ 1),
            "_eaaa");

  TTS_EQUAL(run_test<true>(1,
                           22,
                           /*where to expensive*/
                           {
                               // clang-format off
                               1, 2, 3, 4,
                               5, 6, 7, 8,
                               9, 10, 11, 12,
                               13, 14, 15, 16,
                               17, 18, 19, 20,
                               21, 22
                               // clang-format on
                           },
                           /*stop at*/ 10),
            "ieee"
            "eeee"
            "eeea");
  TTS_EQUAL(run_test<false>(1,
                           22,
                           /*where to expensive*/
                           {
                               // clang-format off
                               1, 2, 3, 4,
                               5, 6, 7, 8,
                               9, 10, 11, 12,
                               13, 14, 15, 16,
                               17, 18, 19, 20,
                               21, 22
                               // clang-format on
                           },
                           /*stop at*/ 10),
            "_eee"
            "eeee"
            "eeea"
            "a");
};
