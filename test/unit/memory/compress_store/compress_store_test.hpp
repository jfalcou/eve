//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core/regular/compress_store.hpp>

#include <algorithm>
#include <array>
#include <random>

template <typename T, typename L, typename C>
void ignore_test(T x, L m, C c)
{
  using e_t = eve::element_type_t<T>;
  using arr = std::array<e_t, T::size()>;

  // gcc bug workaround
  arr x_arr;
  eve::store(x, x_arr.data());

  arr expected;
  expected.fill(e_t{0});

  int f_i = c.offset(eve::as(x));
  int l_i = f_i + c.count(eve::as(x));
  int o = f_i;

  for (int i = f_i; i != l_i; ++i) {
    if (!m.get(i)) continue;
    expected[o++] = x_arr[i];
  }

  alignas(sizeof(arr)) arr actual;
  actual.fill(e_t{0});

  e_t* out = eve::unsafe(eve::compress_store[c])(x, m, actual.begin());
  TTS_EQUAL((out - actual.begin()), o);
  TTS_EQUAL(T(expected.begin()), T(actual.begin()));

  using ap_t = eve::aligned_ptr<e_t, eve::cardinal_t<T>>;
  actual.fill(e_t{0});

  out = eve::unsafe(eve::compress_store[c])(x, m, ap_t{actual.begin()});
  TTS_EQUAL((out - actual.begin()), o);
  TTS_EQUAL(T(expected.begin()), T(actual.begin()));
}

template <typename T, typename L>
void all_ignore_tests(T x, L m)
{
  if (x.size() < 16)
  {
    for (int i = 0; i != x.size() + 1; ++i) {
      for (int j = 0; j <= x.size() - i; ++j) {
        ignore_test(x, m, eve::ignore_extrema{i, j});
      }
    }
  }
  else
  {
    for (int i = 0; i != x.size() + 1; ++i) {
      ignore_test(x, m, eve::ignore_first(i));
      ignore_test(x, m, eve::ignore_last(i));
    }
  }
}

template < typename L, typename T>
void precise_tests(T x)
{
  using e_t = eve::element_type_t<T>;

  // ignore all
  {
    e_t data;
    eve::unsafe(eve::compress_store[eve::ignore_all])(x, L{}, &data + 1);
    eve::safe(eve::compress_store[eve::ignore_all])(x, L{}, &data + 1);
  }

  // writing exactly,
  e_t data[2] = { e_t{0}, e_t{5}} ;
  L mask{false};
  mask.set(T::size() - 1, true);

  eve::safe(eve::compress_store)(x, mask, &data[0]);

  TTS_EQUAL(data[0], x.back());
  TTS_EQUAL(data[1], e_t{5});

  // unsafe with ignore still acts as safe
  data[0] = e_t{0};
  eve::unsafe(eve::compress_store[eve::ignore_first(0)])(x, mask, &data[0]);
  TTS_EQUAL(data[0], x.back());
  TTS_EQUAL(data[1], e_t{5});
}

template <bool all_options, typename T, typename L>
void one_test(T x, L m)
{
  using e_t = eve::element_type_t<T>;
  using arr = std::array<e_t, T::size()>;

  arr expected;
  expected.fill(e_t{0});

  int o = 0;
  for (int i = 0; i != T::size(); ++i) {
    if (!m.get(i)) continue;
    expected[o++] = x.get(i);
  }

  alignas(sizeof(arr)) arr actual;
  actual.fill(e_t{0});

  e_t* out = eve::unsafe(eve::compress_store)(x, m, actual.begin());
  TTS_EQUAL((out - actual.begin()), o);

  // No guarantees past the out
  std::copy(&expected[o], expected.end(), &actual[o]);
  TTS_EQUAL(T(expected.begin()), T(actual.begin()));

  // Same check for aligned
  if constexpr (all_options)
  {
    using ap_t = eve::aligned_ptr<e_t, eve::cardinal_t<T>>;

    actual.fill(e_t{0});
    out = eve::unsafe(eve::compress_store)(x, m, ap_t{actual.begin()});

    TTS_EQUAL((out - actual.begin()), o);

    std::copy(&expected[o], expected.end(), &actual[o]);
    TTS_EQUAL(T(expected.begin()), T(actual.begin()));
  }

  if constexpr (all_options)
  {
    all_ignore_tests(x, m);
  }
}

template <typename L, typename T>
void go_through_everything(T x)
{
  L m(false);
  auto test = [&](auto& self, std::size_t i) mutable {
    if (i == T::size()) {
      one_test<false>(x, m);
      return;
    };
    self(self, i + 1);
    m.set(i, true);
    self(self, i + 1);
  };
  test(test, 0);
}

template<typename L, typename T>
void smaller_test_v(T x)
{
  {
    // even elements
    {
      L m {false};

      for( std::ptrdiff_t i = 0; i < T::size(); i += 2 )
      {
        m.set(i, true);
        one_test<true>(x, m);
      }
    }

    // all/none
    {
      one_test<true>(x, L {true});
      one_test<true>(x, L {false});
    }
    // bunch of randoms
    {
      constexpr auto seed =
          sizeof(eve::element_type_t<L>) + sizeof(eve::element_type_t<T>) + T::size();
      std::mt19937                         g(seed);
      std::uniform_int_distribution<short> d(0, 1);

      auto random_l = [&]() mutable
      {
        L m {false};
        for( int i = 0; i != L::size(); ++i ) { m.set(i, d(g) == 1); }
        return m;
      };

      for( int i = 0; i < 100; ++i ) { one_test<false>(x, random_l()); }
    }

    // precise
    precise_tests<L>(x);
  }
}

template <typename L, typename T>
void all_tests_for_v(T x)
{
  if constexpr (T::size() <= 8)
  {
    go_through_everything<L>(x);
  }
  smaller_test_v<L>(x);
}
