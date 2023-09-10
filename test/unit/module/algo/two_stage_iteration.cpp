//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

namespace
{

template<typename I> struct test_delegate
{
  I                base;
  std::ptrdiff_t   stop_at;
  std::vector<int> left;

  test_delegate(I base, std::ptrdiff_t stop_at, std::vector<int> left)
      : base(base)
      , stop_at(stop_at)
      , left(std::move(left))
  {}

  std::ptrdiff_t left_for_stage1()
  {
    TTS_EXPECT_NOT(left.empty(), REQUIRED);
    auto r = left.at(0);
    left.erase(left.begin());
    return r;
  }

  void fill(char *& f, std::ptrdiff_t length, char what) const
  {
    while( length-- ) *f++ = what;
  }

  bool tail(I f, auto ignore)
  {
    auto tgt = eve::as<eve::wide_value_type_t<I>> {};

    auto ptr = eve::unalign(f.ptr);
    fill(ptr, ignore.offset(tgt), 'i');
    fill(ptr, ignore.count(tgt), 't');
    fill(ptr, ignore.roffset(tgt), 'i');

    return (f - base) == stop_at;
  }

  bool step_1(I f)
  {
    auto ptr = eve::unalign(f.ptr);
    fill(ptr, eve::iterator_cardinal_v<I>, 'a');
    return (f - base) == stop_at;
  }

  bool step_2(I f)
  {
    auto ptr = eve::unalign(f.ptr);
    fill(ptr, eve::iterator_cardinal_v<I>, 'b');
    return (f - base) == stop_at;
  }
};

std::string
run_test(auto traits, int offset, int length, std::vector<int> left, int stop_at = -1)
{
  TTS_EXPECT(length, REQUIRED);

  alignas(64) std::array<char, 100u> buf;
  buf.fill(0);

  std::fill(buf.begin(), buf.begin() + offset, '_');

  auto f = eve::algo::ptr_iterator<char *, eve::fixed<4>> {buf.data() + offset};
  auto l = f + length;

  auto          iteration = eve::algo::two_stage_iteration(traits, f, l);
  test_delegate delegate(iteration.base, stop_at, std::move(left));
  iteration(delegate);
  return std::string(buf.data());
}

TTS_CASE("eve.algo two_stage_iteration, aligned, tails")
{
  auto run = [](int offset, int length, std::vector<int> left = {0})
  { return run_test(eve::algo::traits {}, offset, length, std::move(left)); };

  TTS_EQUAL("tiii", run(0, 1));
  TTS_EQUAL("ttii", run(0, 2));
  TTS_EQUAL("ttti", run(0, 3));
  TTS_EQUAL("tttt", run(0, 4));

  TTS_EQUAL("itii", run(1, 1));
  TTS_EQUAL("itti", run(1, 2));
  TTS_EQUAL("ittt", run(1, 3));

  TTS_EQUAL("ittt"
            "ttii",
            run(1, 5));

  TTS_EQUAL("iiit"
            "bbbb"
            "ttii",
            run(3, 7));
};

TTS_CASE("eve.algo two_stage_iteration, no aligning, tails")
{
  auto run = [](int offset, int length, std::vector<int> left = {0})
  { return run_test(eve::algo::traits {eve::algo::no_aligning}, offset, length, std::move(left)); };

  TTS_EQUAL("tiii", run(0, 1));
  TTS_EQUAL("ttii", run(0, 2));
  TTS_EQUAL("ttti", run(0, 3));
  TTS_EQUAL("bbbb", run(0, 4));

  TTS_EQUAL("_"
            "tiii",
            run(1, 1));
  TTS_EQUAL("_"
            "ttii",
            run(1, 2));
  TTS_EQUAL("_"
            "ttti",
            run(1, 3));

  TTS_EQUAL("_"
            "bbbb"
            "tiii",
            run(1, 5));

  TTS_EQUAL("___"
            "bbbb"
            "ttti",
            run(3, 7));
};

TTS_CASE("eve.algo two_stage_iteration, no aligning, divisble, tails")
{
  auto run = [](int offset, int length, std::vector<int> left = {0})
  {
    return run_test(eve::algo::traits {eve::algo::no_aligning, eve::algo::divisible_by_cardinal},
                    offset,
                    length,
                    std::move(left));
  };

  TTS_EQUAL("_"
            "bbbb",
            run(1, 4));
  TTS_EQUAL("_"
            "bbbb"
            "bbbb",
            run(1, 8));
};

TTS_CASE("eve.algo two_stage_iteration, main")
{
  auto run = [](int offset, int length, std::vector<int> left = {0})
  { return run_test(eve::algo::traits {}, offset, length, std::move(left)); };

  TTS_EQUAL("ittt"
            "aaaa"
            "tiii",
            run(1, 8, {5, 5}));

  TTS_EQUAL("ittt"
            "aaaa"
            "aaaa"
            "tiii",
            run(1, 12, {10, 5}));

  TTS_EQUAL("ittt"
            "aaaa"
            "bbbb"
            "tiii",
            run(1, 12, {5, 3}));

  TTS_EQUAL("ittt"
            "aaaa"
            "aaaa"
            "bbbb"
            "tiii",
            run(1, 16, {10, 3}));

  TTS_EQUAL("ittt"
            "aaaa"
            "bbbb"
            "bbbb"
            "tiii",
            run(1, 16, {5, 3}));
};

} // namespace
