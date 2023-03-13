//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/iteration_test.hpp"

namespace
{

TTS_CASE("eve.algo for_each_iteration_fixed_overflow, selection")
{
  algo_test::iteration_fixture fix;

  auto f   = fix.unaligned_begin() + 3;
  auto l   = f + 40;
  auto a_f = fix.aligned_begin();

  using u_it = decltype(f);
  using a_it = decltype(fix.aligned_begin());

  // aligning
  {
    auto tr  = eve::algo::traits();
    auto sel = eve::algo::for_each_iteration_fixed_overflow(tr, f, l);
    TTS_TYPE_IS(
        decltype(sel),
        (eve::algo::detail::for_each_iteration_fixed_overflow_aligning<decltype(tr), u_it, u_it>));

    TTS_EQUAL(sel.base, fix.aligned_begin());
    TTS_TYPE_IS(decltype(sel.base), a_it);
  }

  // precise f, l
  {
    auto tr  = eve::algo::traits(eve::algo::no_aligning, eve::algo::divisible_by_cardinal);
    auto sel = eve::algo::for_each_iteration_fixed_overflow(tr, f, l);

    TTS_TYPE_IS(decltype(sel),
                (eve::algo::detail::
                     for_each_iteration_fixed_overflow_precise_f_l<decltype(tr), u_it, u_it>));

    TTS_EQUAL(sel.base, f);
    TTS_TYPE_IS(decltype(sel.base), u_it);
  }

  // precise f
  {
    auto tr  = eve::algo::traits(eve::algo::no_aligning);
    auto sel = eve::algo::for_each_iteration_fixed_overflow(tr, f, l);

    TTS_TYPE_IS(
        decltype(sel),
        (eve::algo::detail::for_each_iteration_fixed_overflow_precise_f<decltype(tr), u_it, u_it>));

    TTS_EQUAL(sel.base, f);
    TTS_TYPE_IS(decltype(sel.base), u_it);
  }

  // aligned f
  {
    auto tr  = eve::algo::traits();
    auto sel = eve::algo::for_each_iteration_fixed_overflow(tr, a_f, l);

    TTS_TYPE_IS(
        decltype(sel),
        (eve::algo::detail::for_each_iteration_fixed_overflow_precise_f<decltype(tr), a_it, u_it>));

    TTS_EQUAL(sel.base, a_f);
    TTS_TYPE_IS(decltype(sel.base), a_it);
  }
};

std::string
run_uu_test(int offset, int size, int stop_at = -1, auto... tr)
{
  return algo_test::run_uu_test(eve::algo::for_each_iteration_fixed_overflow,
                                eve::algo::traits {tr...},
                                offset,
                                size,
                                stop_at);
}

TTS_CASE("eve.algo for_each_iteration overflow, aligning, unroll 1, overflow 2 wides")
{
  auto run = [](int offset, int size, int stop_at = -1)
  { return run_uu_test(offset, size, stop_at, eve::algo::unroll<1>, eve::algo::overflow<8>); };
  TTS_EQUAL(run(0, 1), "aiii");
  TTS_EQUAL(run(1, 1), "iaii");
  TTS_EQUAL(run(2, 1), "iiai");
  TTS_EQUAL(run(3, 1), "iiia");
  TTS_EQUAL(run(2, 2), "iiaa");
  TTS_EQUAL(run(3, 2), "iiiaaiii");
  TTS_EQUAL(run(2, 5), "iiaaaaai");

  TTS_EQUAL(run(0, 8),
            "aaaa"
            "aaaa");
  TTS_EQUAL(run(1, 8),
            "iaaa"
            "aaaa"
            "Aiii");
  TTS_EQUAL(run(2, 8),
            "iiaa"
            "aaaa"
            "Aaii");
  TTS_EQUAL(run(0, 9),
            "aaaa"
            "aaaa"
            "Aiii");

  TTS_EQUAL(run(0, 16),
            "aaaa"
            "aaaa"
            "Aaaa"
            "aaaa");
  TTS_EQUAL(run(1, 16),
            "iaaa"
            "aaaa"
            "Aaaa"
            "aaaa"
            "Aiii");
  TTS_EQUAL(run(2, 16),
            "iiaa"
            "aaaa"
            "Aaaa"
            "aaaa"
            "Aaii");
  TTS_EQUAL(run(2, 18),
            "iiaa"
            "aaaa"
            "Aaaa"
            "aaaa"
            "Aaaa");
};

TTS_CASE("eve.algo for_each_iteration overflow, divisible, unroll 1, overflow 1 wide")
{
  auto run = [](int offset, int size, int stop_at = -1)
  {
    return run_uu_test(offset,
                       size,
                       stop_at,
                       eve::algo::unroll<1>,
                       eve::algo::overflow<4>,
                       eve::algo::no_aligning,
                       eve::algo::divisible_by_cardinal);
  };

  TTS_EQUAL(run(0, 8),
            "aaaa"
            "Aaaa");
  TTS_EQUAL(run(1, 8),
            "_aaa"
            "aAaa"
            "a");

  TTS_EQUAL(run(0, 16),
            "aaaa"
            "Aaaa"
            "Aaaa"
            "Aaaa");
};

TTS_CASE("eve.algo for_each_iteration overflow, aligning, unroll 2, overflow 3 wide")
{
  auto run = [](int offset, int size, int stop_at = -1)
  { return run_uu_test(offset, size, stop_at, eve::algo::unroll<2>, eve::algo::overflow<12>); };

  TTS_EQUAL(run(0, 13),
            "aaaa"
            "aaaa"
            "bbbb"
            "Aiii");

  TTS_EQUAL(run(0, 18),
            "aaaa"
            "aaaa"
            "bbbb"
            "Aaaa"
            "aaii");

  TTS_EQUAL(run(1, 18),
            "iaaa"
            "aaaa"
            "bbbb"
            "Aaaa"
            "aaai");
};

TTS_CASE("eve.algo for_each_iteration overflow, divisible, unroll 4, overflow 4 wide")
{
  auto run = [](int offset, int size, int stop_at = -1)
  {
    return run_uu_test(offset,
                       size,
                       stop_at,
                       eve::algo::unroll<4>,
                       eve::algo::overflow<16>,
                       eve::algo::no_aligning,
                       eve::algo::divisible_by_cardinal);
  };

  TTS_EQUAL(run(0, 32),
            "aaaabbbbccccdddd"
            "Aaaabbbbccccdddd");

  TTS_EQUAL(run(0, 68),
            "aaaabbbbccccdddd"
            "Aaaabbbbccccdddd"
            "Aaaabbbbccccdddd"
            "Aaaabbbbccccdddd"
            "Aaaa");
};

} // namespace
