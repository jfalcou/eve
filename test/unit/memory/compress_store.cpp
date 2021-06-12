//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/function/compress_store.hpp>

#include <algorithm>
#include <array>
#include <random>

namespace
{
template <bool all_options, typename T, typename L>
void one_test(T x, L m)
{
  using e_t = eve::element_type_t<T>;
  using arr = std::array<e_t, T::size()>;

  arr expected;
  expected.fill(e_t{});

  std::int8_t o = 0;
  for (std::int8_t i = 0; i != T::size(); ++i) {
    if (!m.get(i)) continue;
    expected[o++] = x.get(i);
  }

  alignas(sizeof(arr)) arr actual;
  actual.fill(e_t{});

  e_t* out = eve::unsafe(eve::compress_store)(x, m, actual.begin());
  TTS_EQUAL((out - actual.begin()), o);

  // No guarntees past the out
  std::copy(&expected[o], expected.end(), &actual[o]);
  TTS_EQUAL(T(expected.begin()), T(actual.begin()));

  // Same check for aligned
  if constexpr (all_options)
  {
    using ap_t = eve::aligned_ptr<e_t, T::size() * sizeof(e_t)>;

    out = eve::unsafe(eve::compress_store)(x, m, ap_t{actual.begin()});

    TTS_EQUAL((out - actual.begin()), o);

    std::copy(&expected[o], expected.end(), &actual[o]);
    TTS_EQUAL(T(expected.begin()), T(actual.begin()));
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

template<typename L, typename T> void smaller_test_v(T x)
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
    std::mt19937                         g;
    std::uniform_int_distribution<short> d(0, 1);

    auto random_l = [&]() mutable {
      L m;
      for( int i = 0; i != L::size(); ++i ) { m.set(i, d(g) == 1); }
      return m;
    };

    for( int i = 0; i < 1000; ++i ) { one_test<true>(x, random_l()); }
  }
}

template <typename L, typename T>
void all_tests_for_v(T x)
{
  if constexpr (T::size() <= 16)
  {
    go_through_everything<L>(x);
  }
  smaller_test_v<L>(x);
}

}

EVE_TEST( "Check compress store behavior"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(1),eve::test::logicals(1,2))
        )
<typename T, typename L> (T data, L logical_data)
{
  all_tests_for_v<eve::logical<T>>(data);
  smaller_test_v<L>(logical_data);
};
