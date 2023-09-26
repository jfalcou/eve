//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <random>

constexpr std::ptrdiff_t test_all_permutations = eve::current_api >= eve::sve ? 4 : 8;
constexpr std::ptrdiff_t random_tests_to_run = eve::current_api >= eve::sve ? 100 : 1000;

TTS_CASE_TPL("Check sort results, many permutations", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  T expected([](int i, int) { return i; });

  eve::stack_buffer<T> buf;
  eve::store(expected, buf.ptr());

  auto* f = eve::unalign(buf.ptr());
  auto* l = f + T::size();

  auto run = [&] {
    T x{buf.ptr()};
    TTS_EQUAL(expected, eve::sort(x), REQUIRED) << x;
  };

  if constexpr (T::size() <= test_all_permutations) {
    do {
      run();
    } while (std::next_permutation(f, l));
  } else {
    std::ptrdiff_t count = random_tests_to_run;
    using e_t = eve::element_type_t<T>;
    std::mt19937 rng(sizeof(e_t) + std::is_signed_v<e_t>);

    while (count--) {
      std::shuffle(f, l, rng);
      run();
    }
  }
};

TTS_CASE_TPL("Check sort results, different apis", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  {
    T expected([](int i, int size) { return size - i - 1; });
    T in([](int i, int) { return i; });
    TTS_EQUAL(expected, eve::sort(in, eve::is_greater));
  }
  {
    eve::logical<T> in ([](int i, int) { return i % 3 != 0; });
    eve::logical<T> expected ([](int i, int size) { return i > (size / 3); });

    // false is less than true
    TTS_EQUAL(expected, eve::sort(in, [](auto x, auto y) {
      return eve::logical_andnot(y, x); }));
  }
};
