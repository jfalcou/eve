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

namespace {

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

  alignas(64) std::array<char, 100> data;
};

struct test_delegate {
  char* data;
  std::vector<std::ptrdiff_t> where_to_expensive;
  std::ptrdiff_t expensive_returns_true_at;
  std::ptrdiff_t stop_at = -1;

  std::ptrdiff_t where_to_expensive_pos = 0;
  char* remembered_expesnive = nullptr;

  test_delegate(
    char* data,
    std::vector<std::ptrdiff_t> where_to_expensive,
    std::ptrdiff_t expensive_returns_true_at = -1,
    std::ptrdiff_t stop_at = -1
  ) : data(data),
      where_to_expensive(where_to_expensive),
      expensive_returns_true_at(expensive_returns_true_at),
      stop_at(stop_at) {}

  eve::algo::continue_break_expensive step(auto it, auto ignore) {

    auto  tgt = eve::as<eve::wide<std::int8_t, eve::fixed<4>>> {};
    char *ptr = it.ptr;

    std::ptrdiff_t it_idx = it.ptr - data;
    std::cerr << "step: it idx: " << it_idx << " ignore: " << ignore << std::endl;

    for( std::ptrdiff_t i = ignore.offset(tgt); i; --i ) { *ptr++ = 'i'; }
    for( std::ptrdiff_t i = ignore.count(tgt); i; --i ) {
      *ptr++ = 'a';
    }
    for( std::ptrdiff_t i = ignore.roffset(tgt); i; --i ) { *ptr++ = 'i'; }

    if (where_to_expensive_pos < std::ssize(where_to_expensive)) {
      auto next_expensive = where_to_expensive[where_to_expensive_pos];

      if ( it_idx <= next_expensive && next_expensive < it_idx + 4 ) {
        remembered_expesnive = data + next_expensive;
        return eve::algo::continue_break_expensive::expensive;
      }
    }

    if ( stop_at != -1 && stop_at < it_idx + 4) {
      return eve::algo::continue_break_expensive::break_;
    }
    return eve::algo::continue_break_expensive::continue_;
  }

  bool expensive_part() {
    *remembered_expesnive = 'e';
    if (remembered_expesnive - data == expensive_returns_true_at) {
      return true;
    }
    return false;
  }
};

template <bool align, int unroll>
struct run_test_impl {
  int offset;
  int size;
  std::vector<std::ptrdiff_t> where_to_expensive;
  int expensive_returns_true_at;
  int stop_at;


  template <bool divisible>
  std::string run_impl(
    auto& fix,
    auto f,
    auto l
  ) {
    test_delegate d {
      fix.data.data(),
      where_to_expensive,
      expensive_returns_true_at,
      stop_at
    };

    auto iter = eve::algo::for_each_iteration_with_expensive_optional_part(
      []{
        if constexpr (align && !divisible) {
          return eve::algo::traits{eve::algo::unroll<unroll>};
        } else if constexpr (align && divisible) {
          return eve::algo::traits{eve::algo::divisible_by_cardinal, eve::algo::unroll<unroll>};
        } else if constexpr (!align && !divisible) {
          return eve::algo::traits{eve::algo::no_aligning, eve::algo::unroll<unroll>};
        } else if constexpr (!align && divisible) {
          return eve::algo::traits{
            eve::algo::no_aligning, eve::algo::divisible_by_cardinal, eve::algo::unroll<unroll>
          };
        }
      }(),
      f,
      l
    );
    iter(d);
    return std::string(fix.res());
  }

  std::string operator()() {
    std::string res;
    {
      fixture fix;
      auto f = fix.unaligned_begin() + offset;
      auto l = f + size;
      res = run_impl<false>(fix, f, l);
    }

    // just aligned
    if (offset % 4 == 0) {
      std::string res1;
      fixture fix;
      auto f = fix.aligned_begin() + offset;
      auto l = eve::unalign(f) + size;
      res1 = run_impl<false>(fix, f, l);
      TTS_EQUAL(res, res1);
    }

    // just divisible
    if (size % 4 == 0) {
      std::string res1;
      fixture fix;
      auto f = fix.unaligned_begin() + offset;
      auto l = eve::unalign(f) + size;
      res1 = run_impl<true>(fix, f, l);
      TTS_EQUAL(res, res1);
    }

    // 1. align/unaling divisible
    if (offset % 4 == 0 && size % 4 == 0) {
      std::string res1;
      fixture fix;
      auto f = fix.aligned_begin() + offset;
      auto l = eve::unalign(f) + size;
      res1 = run_impl<true>(fix, f, l);
      TTS_EQUAL(res, res1);
    }

    // 2. aligned both ends
    if (offset % 4 == 0 && size % 4 == 0) {
      std::string res1;
      fixture fix;
      auto f = fix.aligned_begin() + offset;
      auto l = f + size;
      res1 = run_impl<true>(fix, f, l);
      TTS_EQUAL(res, res1);
    }

    return res;
  }
};

template <bool align>
std::string
run_test(
  int offset,
  int size,
  std::vector<std::ptrdiff_t> where_to_expensive = {},
  int expensive_returns_true_at = -1,
  int stop_at = -1
) {
  std::string unroll1 = run_test_impl<align, 1>{
    offset,
    size,
    where_to_expensive,
    expensive_returns_true_at,
    stop_at
  }();

  std::string unroll2 = run_test_impl<align, 2>{
    offset,
    size,
    where_to_expensive,
    expensive_returns_true_at,
    stop_at
  }();

  std::string unroll4 = run_test_impl<align, 4>{
    offset,
    size,
    where_to_expensive,
    expensive_returns_true_at,
    stop_at
  }();

  TTS_EQUAL(unroll1, unroll2);
  TTS_EQUAL(unroll1, unroll4);
  return unroll1;
}

}  // namespace

TTS_CASE("eve.algo.for_each_iteration_with_expensive_optional_part, aligning, no matches") {
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

TTS_CASE("eve.algo.for_each_iteration_with_expensive_optional_part, no aligning, no matches") {
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

TTS_CASE("eve.algo.for_each_iteration_with_expensive_optional_part, aligning, some expensive") {
  TTS_EQUAL(run_test<true>(
    0, 1,
    /*where to expensive*/ {0}
  ),
  "eiii");
  TTS_EQUAL(run_test<true>(
    0, 4,
    /*where to expensive*/ {0, 1, 2, 3}
  ),
  "eaaa");

};
