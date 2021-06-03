//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

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
      return eve::algo::aligned_ptr_iterator<const int, eve::fixed<4>> {
        eve::aligned_ptr<const int, 4 * sizeof(int)>(data.begin())
      };
    }

    auto aligned_end() const { return aligned_begin() + data.size(); }

    auto unaligned_begin() const { return aligned_begin().unaligned(); }
    auto unaligned_end()   const { return aligned_end().unaligned(); }

    alignas(sizeof(int) * 4) std::array<int, 100> data;
  };
}

TTS_CASE("eve.algo for_each_iteration, selection")
  {
    fixture fix;

    auto f = fix.unaligned_begin() + 3;
    auto l = f + 40;

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
}

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

    bool step(auto it, eve::relative_conditional_expr auto ignore)
    {
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
    if (expected.size() != del.res.size()) return;

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
    run_test(eve::algo::traits(eve::algo::unroll<4>), f, l, -1, expected);
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
}

TTS_CASE("eve.algo for_each_iteration border cases, precise")
{
  fixture fix;

  auto test = [](auto f, auto l, test_res expected){
    auto traits = eve::algo::traits(eve::algo::no_aligning, eve::algo::unroll<4>);
    run_test(traits, f, l, -1, expected);

    if ((f - l) % 4 == 0) {
      run_test(eve::algo::default_to(
        traits, eve::algo::traits(eve::algo::divisible_by_cardinal)),
        f, l, -1, expected);
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
}
