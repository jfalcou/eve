//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include "test.hpp"

#include <algorithm>
#include <array>
#include <random>

template <typename T, typename L, typename ... MaybeIgnore>
auto make_expected(T x_, L m_, MaybeIgnore ... ignore )
{
  if constexpr (sizeof...(ignore)) {
    m_ = m_ && to_logical(ignore..., eve::as(m_));
  }

  eve::stack_buffer<T> x;
  eve::store(x_, x.ptr());
  auto x_ptr = eve::unalign(x.ptr());

  eve::stack_buffer<L> m;
  eve::store(m_, m.ptr());
  auto m_ptr = eve::unalign(m.ptr());

  std::array<eve::element_type_t<T>, T::size()> r;
  r.fill(eve::zero(eve::as<eve::element_type_t<T>>{}));

  auto o = r.begin();

  for (std::size_t i = 0; i != T::size(); ++i) {
    if (m_ptr[i]) *o++ = x_ptr[i];
  }

  return r;
}

template <typename T, typename L, typename ... MaybeIgnore>
auto make_actual(T x, L m, MaybeIgnore ... ignore )
{
  std::array<eve::element_type_t<T>, T::size()> r;

  auto* o = r.data();

  auto actual_tuple = eve::compress(ignore..., x, m);
  kumi::for_each([&](auto compressed_lengh) {
    auto [compressed, length] = compressed_lengh;
    eve::store(compressed, o);
    o += length;
  }, actual_tuple);

  std::fill(o, r.data() + r.size(), eve::zero(eve::as<eve::element_type_t<T>>{}));
  return r;
}


template <typename T, typename L, typename ... MaybeIgnore>
void one_test(T x, L m, MaybeIgnore ... ignore )
{
  auto expected = make_expected(x, m, ignore...);
  auto actual = make_actual(x, m, ignore...);
  ((TTS_EQUAL(expected, actual) << "x: " << x << "m: " << m << " ignore: ") << ... << ignore);
  if (expected != actual) {
    std::terminate();
  }
}

template <typename T, typename L>
void all_ignore_tests(T x, L m)
{
  // sve takes very long on emulation

  one_test(x, m);
  one_test(x, m, eve::ignore_all);

  if (eve::current_api >= eve::sve && eve::logical_value<T>)
  {
    one_test(x, m, eve::ignore_first(1));
    return;
  }


  if constexpr (!(eve::current_api >= eve::sve)) {
    if (x.size() < 8 && !(eve::current_api >= eve::sve))
    {
      for (int i = 0; i != x.size() + 1; ++i) {
        for (int j = 0; j <= x.size() - i; ++j) {
          one_test(x, m, eve::ignore_extrema{i, j});
        }
      }
      return;
    }
  }

  if (x.size() < 32)
  {
    for (int i = 0; i < x.size() + 1; i++) {
      one_test(x, m, eve::ignore_first(i));
      one_test(x, m, eve::ignore_last(i));
    }
  }
  else
  {
    for (int i = 0; i < x.size() + 1; i += 20) {
      one_test(x, m, eve::ignore_first(i));
      one_test(x, m, eve::ignore_last(i));
    }
  }
}

template <typename L, typename T>
void go_through_everything(T x)
{
  L m(false);
  auto test = [&](auto& self, std::size_t i) mutable {
    if (i == T::size()) {
      all_ignore_tests(x, m);
      return;
    };
    self(self, i + 1);
    m.set(i, true);
    self(self, i + 1);
  };
  test(test, 0);
}


template<typename L, typename T>
void smaller_test_for(T x)
{
  {
    // even elements
    {
      L m {false};

      for( std::ptrdiff_t i = 0; i < T::size(); i += 2 )
      {
        m.set(i, true);
        all_ignore_tests(x, m);
      }
    }

    // all/none
    {
      all_ignore_tests(x, L {true});
      all_ignore_tests(x, L {false});
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

      int n = 100;
      if (eve::current_api >= eve::sve) n = 20;

      for( int i = 0; i < n; ++i ) { all_ignore_tests(x, random_l()); }
    }
  }
}


template <typename L, typename T>
void compress_test(T x)
{
  if constexpr (T::size() <= 8 && !(eve::current_api >= eve::sve) )
  {
    go_through_everything<L>(x);
  }
  else
  {
    smaller_test_for<L>(x);
  }
}
