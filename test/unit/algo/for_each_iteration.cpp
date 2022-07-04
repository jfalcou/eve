//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/ptr_iterator.hpp>
#include <eve/algo/traits.hpp>

#include <utility>
#include <numeric>
#include <variant>

namespace
{
  struct fixture
  {
    fixture()
    {
      std::iota(data.begin(), data.end(), 0);
    }

    auto aligned_begin() const
    {
      using ap = eve::aligned_ptr<const int, eve::fixed<4>>;
      return eve::algo::ptr_iterator<ap, eve::fixed<4>> {
        ap(data.begin())
      };
    }

    auto aligned_end() const { return aligned_begin() + data.size(); }

    auto unaligned_begin() const { return eve::unalign(aligned_begin()); }
    auto unaligned_end()   const { return eve::unalign(aligned_end()); }

    alignas(sizeof(int) * 4) std::array<int, 100> data;
  };
}

TTS_CASE("eve.algo for_each_iteration, selection")
{
  fixture fix;

  auto f = fix.unaligned_begin() + 3;
  auto l = f + 40;
  auto a_f = fix.aligned_begin();

  using u_it = decltype(f);
  using a_it = decltype(fix.aligned_begin());

  // aligning
  {
    auto tr  = eve::algo::traits();
    auto sel = eve::algo::for_each_iteration(tr, f, l);
    TTS_TYPE_IS(decltype(sel),
                (eve::algo::detail::for_each_iteration_aligning<decltype(tr), u_it, u_it>));

    TTS_EQUAL(sel.base, fix.aligned_begin());
    TTS_TYPE_IS(decltype(sel.base), a_it);
  }

  // precise f, l
  {
    auto tr  = eve::algo::traits(eve::algo::no_aligning, eve::algo::divisible_by_cardinal);
    auto sel = eve::algo::for_each_iteration(tr, f, l);

    TTS_TYPE_IS(decltype(sel),
                (eve::algo::detail::for_each_iteration_precise_f_l<decltype(tr), u_it, u_it>));

    TTS_EQUAL(sel.base, f);
    TTS_TYPE_IS(decltype(sel.base), u_it);
  }

  // precise f
  {
    auto tr  = eve::algo::traits(eve::algo::no_aligning);
    auto sel = eve::algo::for_each_iteration(tr, f, l);

    TTS_TYPE_IS(decltype(sel),
                (eve::algo::detail::for_each_iteration_precise_f<decltype(tr), u_it, u_it>));

    TTS_EQUAL(sel.base, f);
    TTS_TYPE_IS(decltype(sel.base), u_it);
  }

  // aligned f
  {
    auto tr  = eve::algo::traits();
    auto sel = eve::algo::for_each_iteration(tr, a_f, l);

    TTS_TYPE_IS(decltype(sel),
                (eve::algo::detail::for_each_iteration_precise_f<decltype(tr), a_it, u_it>));

    TTS_EQUAL(sel.base, a_f);
    TTS_TYPE_IS(decltype(sel.base), a_it);
  }
};

namespace
{

  struct ignore
  {
    std::variant<eve::ignore_none_, eve::ignore_first,
                 eve::ignore_last, eve::ignore_extrema,
                 eve::keep_first> body;

    ignore(eve::relative_conditional_expr auto expr) : body(expr) {}

    friend bool operator==(ignore const& x, ignore const& y) = default;

    friend std::ostream& operator<<(std::ostream& out, ignore const& x) {
      return std::visit([&](auto elem) -> decltype(auto) { return out << elem; }, x.body);
    }

    std::ptrdiff_t count() const {
      auto as = eve::as<eve::wide<int, eve::fixed<4>>>{};
      return std::visit([&](auto elem) { return elem.count(as); }, body);
    }

  };

  using test_res = std::vector<std::pair<std::ptrdiff_t, ignore>>;

  template <typename I>
  struct test_delegate
  {
    test_delegate(I base, std::ptrdiff_t stop_at) :
      base{base},
      stop_at(stop_at) {}

    I base;
    std::ptrdiff_t stop_at;
    test_res res;

    std::vector<std::ptrdiff_t> step_idxes;

    template <std::ptrdiff_t idx>
    bool step(auto it, eve::relative_conditional_expr auto ignore, eve::index_t<idx>)
    {
      // Separate test to proper test indexing
      step_idxes.push_back(idx);
      res.emplace_back(it - base, ignore);
      return stop_at == (it - base);
    }

    template <std::size_t size>
    bool unrolled_step(std::array<I, size> arr)
    {
      res.emplace_back(arr[0] - base, eve::ignore_none);
      return stop_at == (arr[0] - base);
    }
  };

  template <typename Traits, typename I, typename S>
  void run_test(Traits traits, I f, S l, std::ptrdiff_t stop_at, test_res expected)
  {
    auto iteration = eve::algo::for_each_iteration(traits, f, l);
    test_delegate del{iteration.base, stop_at};
    iteration(del);
    TTS_EQUAL(expected.size(), del.res.size());
    if (expected.size() != del.res.size()) {
      std::cout << "expected : {" << std::endl;
      for (auto const& e : expected) {
         std::cout << e.first << ' ' << e.second << std::endl;
      }
      std::cout << "}" << std::endl;
      std::cout << "actual : {" << std::endl;
      for (auto const& e : del.res) {
         std::cout << e.first << ' ' << e.second << std::endl;
      }
      std::cout << "}" << std::endl;
    }

    for (std::size_t i = 0; i != del.res.size(); ++i) {
      TTS_EQUAL(del.res[i].first,  expected[i].first);
      TTS_EQUAL(del.res[i].second, expected[i].second);
    }
  }

}

TTS_CASE("eve.algo for_each_iteration border cases, aligning")
{
  fixture fix;

  auto test = [](auto f, auto l, test_res expected){
    run_test(eve::algo::traits(), f, l, -1, expected);

    if (expected.size() > 1) expected.pop_back();
    run_test(eve::algo::traits(), f, l, 0, expected);
  };

  // <= wide
  {
    auto f = fix.unaligned_begin();
    auto l = f + 4;

    for (int i = 0; i != 4; ++i)
    {
      test(f + i, l, {{0, eve::ignore_first(i)}});
    }

    for (int i = 3; i != 0; --i)
    {
      test(f, l - i, {{0, eve::ignore_extrema(0, i)}});
    }

    test(f + 1, l - 1, {{0, eve::ignore_extrema(1, 1)}});
    test(f + 2, l - 1, {{0, eve::ignore_extrema(2, 1)}});
    test(f + 1, l - 2, {{0, eve::ignore_extrema(1, 2)}});
  }

  //  <= two wides
  {
    auto f = fix.unaligned_begin();
    auto l = f + 8;

    test(f, l, {{0, eve::ignore_first(0)}, {4, eve::ignore_none}});

    for (int i = 1; i != 4; ++i)
    {
      test(f + i, l    , {{0, eve::ignore_first(i)}, {4, eve::ignore_none}});
      test(f    , l - i, {{0, eve::ignore_first(0)}, {4, eve::ignore_extrema(0, i)}});
      test(f + i, l - i, {{0, eve::ignore_first(i)}, {4, eve::ignore_extrema(0, i)}});
    }
  }
};

TTS_CASE("eve.algo for_each_iteration border cases, precise")
{
  fixture fix;

  auto one_test = [](auto traits, auto f, auto l, test_res expected) {
     run_test(traits, f, l, -1, expected);
     if (expected.size() > 1) expected.pop_back();
     run_test(traits, f, l, 0, expected);
  };

  auto test = [&](auto f, auto l, test_res expected){
    one_test(eve::algo::traits(eve::algo::no_aligning), f, l, expected);

    if ((f - l) % 4 == 0) {
      auto traits = eve::algo::traits(eve::algo::no_aligning, eve::algo::divisible_by_cardinal);
      one_test(traits, f, l, expected);
    }
  };

  // <= wide
  {
    auto f = fix.unaligned_begin();
    auto l = f + 4;

    test(f, l, {{0, eve::ignore_none}});

    for (int i = 1; i != 4; ++i)
    {
      test(f + i, l, {{0, eve::keep_first(4 - i)}});
    }

    for (int i = 3; i != 0; --i)
    {
      test(f, l - i, {{0, eve::keep_first(4 - i)}});
    }

    test(f + 1, l - 1, {{0, eve::keep_first(2)}});
    test(f + 2, l - 1, {{0, eve::keep_first(1)}});
    test(f + 1, l - 2, {{0, eve::keep_first(1)}});
  }

  //  <= two wides
  {
    auto f = fix.unaligned_begin();
    auto l = f + 8;

    test(f, l, {{0, eve::ignore_none}, {4, eve::ignore_none}});

    for (int i = 1; i != 4; ++i)
    {
      test(f + i, l    , {{0, eve::ignore_none}, {4, eve::keep_first(4 - i)}});
      test(f    , l - i, {{0, eve::ignore_none}, {4, eve::keep_first(4 - i)}});
    }

    test(f + 1, l - 1, {{0, eve::ignore_none}, {4, eve::keep_first(2)}});
    test(f + 1, l - 2, {{0, eve::ignore_none}, {4, eve::keep_first(1)}});
    test(f + 2, l - 1, {{0, eve::ignore_none}, {4, eve::keep_first(1)}});
  }
};

TTS_CASE("eve.algo for_each_iteration unrolling, aligning")
{
  fixture fix;
  auto f = fix.unaligned_begin();

  auto test = [&](auto traits, auto overall_l, test_res expected) {
    auto l = f + expected.back().first + expected.back().second.count();
    run_test(traits, f, l, -1, expected);
    // stop test
    run_test(traits, f, overall_l, expected.back().first, expected);
  };

  auto pattern_test = [&](auto unroll, test_res pattern) {
    auto overall_l = f + pattern.back().first + pattern.back().second.count();

    for (auto up_to = pattern.begin() + 1; up_to != pattern.end(); ++up_to) {
      auto traits = eve::algo::traits(unroll);
      test(traits, overall_l, {pattern.begin(), up_to});
    }
  };

  // no unrolling
  pattern_test(
    eve::algo::unroll<1>,
    {
      {0, eve::ignore_first(0)},
      {4, eve::ignore_none},
      {8, eve::ignore_none},
      {12, eve::ignore_none},
      {16, eve::ignore_none},
      {20, eve::ignore_none},
      {24, eve::ignore_extrema(0, 2)},
    }
  );

  // unroll 2
  pattern_test(
    eve::algo::unroll<2>,
    {
      {0, eve::ignore_first(0)},
      {4, eve::ignore_none},
      {8, eve::ignore_none},
      // unrolling starts
      {12, eve::ignore_none},
      {20, eve::ignore_none},
      {28, eve::ignore_none},
      {36, eve::ignore_none},
      // unrolling ends
      {44, eve::ignore_extrema(0, 2)},
    }
  );

  // unroll 3
  pattern_test(
    eve::algo::unroll<3>,
    {
      {0, eve::ignore_first(0)},
      {4, eve::ignore_none},
      {8, eve::ignore_none},
      {12, eve::ignore_none},
      // unrolling starts
      {16, eve::ignore_none},
      {28, eve::ignore_none},
      // unrolling ends
      {40, eve::ignore_none},
      {44, eve::ignore_none},
      {48, eve::ignore_extrema(0, 3)}
    }
  );

  // unroll 4
  pattern_test(
    eve::algo::unroll<4>,
    {
      {0, eve::ignore_first(0)},
      {4, eve::ignore_none},
      {8, eve::ignore_none},
      {12, eve::ignore_none},
      {16, eve::ignore_none},
      // unrolling starts
      {20, eve::ignore_none},
      {36, eve::ignore_none},
      {52, eve::ignore_none},
      // unrolling ends
      {68, eve::ignore_none},
      {72, eve::ignore_none},
      {76, eve::ignore_none},
      {80, eve::ignore_extrema(0, 1)}
    }
  );
};

TTS_CASE("eve.algo for_each_iteration unrolling, precise")
{
  fixture fix;
  auto f = fix.unaligned_begin();

  auto test = [&](auto traits, auto overall_l, test_res expected) {
    auto l = f + expected.back().first + expected.back().second.count();
    run_test(traits, f, l, -1, expected);
    // stop test
    run_test(traits, f, overall_l, expected.back().first, expected);
  };

  auto pattern_test = [&](auto unroll, test_res pattern) {
    auto overall_l = f + pattern.back().first + pattern.back().second.count();

    for (auto up_to = pattern.begin() + 1; up_to != pattern.end(); ++up_to) {
      auto traits = eve::algo::traits(unroll, eve::algo::no_aligning);
      test(traits, overall_l, {pattern.begin(), up_to});
    }

    pattern.pop_back();
    overall_l = f + pattern.back().first + 4;
    for (auto up_to = pattern.begin() + 1; up_to != pattern.end(); ++up_to) {
      auto traits = eve::algo::traits(unroll, eve::algo::no_aligning, eve::algo::divisible_by_cardinal);
      test(traits, overall_l, {pattern.begin(), up_to});
    }
  };

  // no unrolling
  pattern_test(
    eve::algo::unroll<1>,
    {
      {0, eve::ignore_none},
      {4, eve::ignore_none},
      {8, eve::ignore_none},
      {12, eve::ignore_none},
      {16, eve::ignore_none},
      {20, eve::ignore_none},
      {24, eve::keep_first(2)},
    }
  );

  // unroll 2
  pattern_test(
    eve::algo::unroll<2>,
    {
      {0, eve::ignore_none},
      {4, eve::ignore_none},
      // unrolling starts
      {8, eve::ignore_none},
      {16, eve::ignore_none},
      {24, eve::ignore_none},
      // unrolling ends
      {32, eve::keep_first(2)},
    }
  );

  // unroll 3
  pattern_test(
    eve::algo::unroll<3>,
    {
      {0, eve::ignore_none},
      {4, eve::ignore_none},
      {8, eve::ignore_none},
      // unrolling starts
      {12, eve::ignore_none},
      {24, eve::ignore_none},
      {36, eve::ignore_none},
      // unrolling ends
      {40, eve::ignore_none},
      {44, eve::keep_first(3)},
    }
  );

  // unroll 4
  pattern_test(
    eve::algo::unroll<4>,
    {
      {0, eve::ignore_none},
      {4, eve::ignore_none},
      {8, eve::ignore_none},
      {12, eve::ignore_none},
      // unrolling starts
      {16, eve::ignore_none},
      {32, eve::ignore_none},
      {48, eve::ignore_none},
      // unrolling ends
      {64, eve::keep_first(1)},
    }
  );
};

TTS_CASE("eve.algo for_each_iteration steps indexing")
{
  fixture fix;

  auto run = [&] (auto traits, int elem_count) {
    auto f = fix.unaligned_begin();
    auto l = f + elem_count;

    auto iteration = eve::algo::for_each_iteration(traits, f, l);
    test_delegate del{iteration.base, -1};
    iteration(del);

    return del.step_idxes;
  };

  auto aligning = run(eve::algo::traits(eve::algo::unroll<4>), 82);
  TTS_EQUAL(aligning, (std::vector<std::ptrdiff_t>{
    0, // ignore,
    0, 1, 2, 3, // steps starting
    0, 1, 2, // steps finishing
    0, // ignore last
  }));

  auto precise = run(
    eve::algo::traits(eve::algo::unroll<4>, eve::algo::no_aligning),
    78);
  TTS_EQUAL(precise, (std::vector<std::ptrdiff_t>{
    0, 1, 2, 3, // steps starting
    0, 1, 2, // steps finishing
    0, // ignore
  }));
};
