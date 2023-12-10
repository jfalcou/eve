//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <numeric>

namespace
{

template<typename T>
T
correct_iota()
{
  using e_t = eve::element_type_t<T>;
  std::array<e_t, T::size()> buf;
  std::iota(buf.begin(), buf.end(), 0);
  return T {buf.data()};
}

template<typename T>
T
correct_iota_masked(eve::logical<T> m, auto else_)
{
  using e_t = eve::element_type_t<T>;
  std::array<e_t, T::size()> buf;

  e_t count = 0;
  for( int i = 0; i != T::size(); ++i )
  {
    buf[i] = m.get(i) ? count : else_;
    ++count;
  }

  return T {buf.data()};
}

TTS_CASE_TPL("eve::iota basic", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  T expected = correct_iota<T>();
  T actual   = eve::iota(eve::as<T> {});

  TTS_EQUAL(expected, actual);
};

TTS_CASE_TPL("eve::iota relative ignore", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  auto ignore_test = [](auto ignore)
  {
    auto m        = ignore.mask(eve::as<T> {});
    T    expected = correct_iota_masked<T>(m, 0);
    T    actual   = eve::iota[ignore](eve::as<T> {});

    TTS_EQUAL(expected, actual, REQUIRED) << ignore;

    expected = correct_iota_masked<T>(m, 5);
    actual   = eve::iota[ignore.else_(5)](eve::as<T> {});
    TTS_EQUAL(expected, actual, REQUIRED) << ignore;
  };

  ignore_test(eve::ignore_all);
  ignore_test(eve::ignore_none);

  for( int i = 0; i != T::size() + 1; ++i )
  {
    ignore_test(eve::ignore_first(i));
    ignore_test(eve::ignore_last(i));
    ignore_test(eve::ignore_extrema(i / 2, i / 2));
  }
};

TTS_CASE_WITH( "Check compress behavior for logicals"
        , eve::test::simd::all_types
        , tts::generate(tts::logicals(1,2))
        )
<typename T> (eve::logical<T> m)
{
  T expected0 = correct_iota_masked<T>(m, 0);
  T actual0 = eve::iota[m](eve::as<T>{});

  TTS_EQUAL(expected0, actual0);

  T expected1 = correct_iota_masked<T>(m, 5);
  T actual1 = eve::iota[eve::if_(m).else_(5)](eve::as<T>{});

  TTS_EQUAL(expected1, actual1);
};

}
