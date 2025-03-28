//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check eve::count_true return type (wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  const T val{};

  TTS_EXPR_IS((eve::count_true(eve::logical<T>())), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[eve::ignore_none](eve::logical<T>())), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[val > 0](eve::logical<T>())), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[true](eve::logical<T>())), std::ptrdiff_t);
};

TTS_CASE_TPL("Check eve::count_true return type (scalar)", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  TTS_EXPR_IS((eve::count_true(eve::logical<T>())), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[eve::ignore_none](eve::logical<T>())), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[true](eve::logical<T>())), std::ptrdiff_t);
};

TTS_CASE("Check eve::count_true return type (edge cases)")
{
  TTS_EXPR_IS((eve::count_true(bool{})), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[eve::ignore_none](bool{})), std::ptrdiff_t);
  TTS_EXPR_IS((eve::count_true[true](bool{})), std::ptrdiff_t);
};

template<typename T, typename U>
std::ptrdiff_t manual_count_true(T v, U mask)
{
  if constexpr (eve::scalar_value<T>)
  {
    return std::ptrdiff_t{v && mask};
  }
  else
  {
    std::ptrdiff_t expected = 0;

    if constexpr (std::same_as<U, bool>)
    {
      for (int i = 0; i < v.size(); ++i)
        if (v.get(i) && mask)
          ++expected;
    }
    else
    {
      for (int i = 0; i < v.size(); ++i)
        if (v.get(i) && mask.get(i))
          ++expected;
    }

    return expected;
  }
}

template<typename T>
void test_count_true(T v)
{
  TTS_EQUAL(eve::count_true(v), manual_count_true(v, true));
  TTS_EQUAL(eve::count_true[true](v), manual_count_true(v, true));
}

TTS_CASE("Check eve::count_true booleans")
{
  TTS_EQUAL(eve::count_true(true), 1);
  TTS_EQUAL(eve::count_true(false), 0);
  TTS_EQUAL(eve::count_true[true](true), 1);
  TTS_EQUAL(eve::count_true[true](false), 0);
  TTS_EQUAL(eve::count_true[false](true), 0);
  TTS_EQUAL(eve::count_true[false](false), 0);
};

TTS_CASE_TPL("Check eve::count_true behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  constexpr auto cardinal = eve::cardinal_v<T>;

  TTS_EQUAL(eve::count_true(eve::true_(eve::as<T>())), cardinal);
  TTS_EQUAL(eve::count_true(eve::false_(eve::as<T>())), 0);

  for( std::ptrdiff_t j = 0; j < cardinal; ++j )
  {
    eve::logical<T> rhs1 = {}, rhs2 = {}, rhs3 = {}, rhs4 = {};

    for( std::ptrdiff_t i = 0; i < cardinal; ++i )
    {
      rhs1.set(i, i >= j ? true : false);
      rhs2.set(i, i <= j ? false : true);
      rhs3.set(i, i == j ? true : false);
      rhs4.set(i, i == j ? false : true);
    }

    test_count_true(rhs1);
    // TTS_EQUAL(eve::count_true(rhs1), (cardinal - j));
    // TTS_EQUAL(eve::count_true(rhs2), (cardinal - j - 1));
    // TTS_EQUAL(eve::count_true(rhs3), 1);
    // TTS_EQUAL(eve::count_true(rhs4), (cardinal - 1));
  }
};

// TTS_CASE_TPL("Check eve::count_true behavior with ignore", eve::test::simd::all_types)
// <typename T>(tts::type<T>)
// {
//   eve::logical<T> data(true);
//   eve::logical<T> data_false(false);
//   constexpr auto cardinal = eve::cardinal_v<T>;

//   TTS_EQUAL(eve::count_true[eve::ignore_none](data), cardinal);
//   TTS_EQUAL(eve::count_true[eve::ignore_all](data), 0);
//   TTS_EQUAL(eve::count_true[eve::ignore_first(cardinal - 1)](data), 1);
//   TTS_EQUAL(eve::count_true[eve::keep_first(cardinal - 1)](data), cardinal - 1);
//   TTS_EQUAL(eve::count_true[eve::ignore_last(cardinal - 1)](data), 1);
//   TTS_EQUAL(eve::count_true[eve::keep_last(cardinal - 1)](data), cardinal - 1);

//   TTS_EQUAL(eve::count_true[eve::ignore_none](data_false), 0);
//   TTS_EQUAL(eve::count_true[eve::ignore_all](data_false), 0);
//   TTS_EQUAL(eve::count_true[eve::ignore_first(cardinal - 1)](data_false), 0);
//   TTS_EQUAL(eve::count_true[eve::keep_first(cardinal - 1)](data_false), 0);
//   TTS_EQUAL(eve::count_true[eve::ignore_last(cardinal - 1)](data_false), 0);
//   TTS_EQUAL(eve::count_true[eve::keep_last(cardinal - 1)](data_false), 0);

//   if constexpr (cardinal >= 2)
//   {
//     TTS_EQUAL(eve::count_true[eve::ignore_first(1) && eve::ignore_last(1)](data), cardinal - 2);

//     auto iota = eve::iota(eve::as<T>());
//     TTS_EQUAL(eve::count_true[iota > 1](data), cardinal - 2);
//     TTS_EQUAL(eve::count_true[iota > 1](data_false), 0);
//   }
// };

// TTS_CASE_TPL("Check eve::count_true top_bits", eve::test::simd::all_types)
// <typename T>(tts::type<T>)
// {
//   eve::logical<T> x(false);

//   auto test = [&]
//   {
//     std::ptrdiff_t expected = 0;
//     for (int i = 0; i != x.size(); ++i) expected += x.get(i);

//     eve::top_bits mmask {x};
//     TTS_EQUAL(eve::count_true(mmask), expected);

//     std::ptrdiff_t expected_c = 0;
//     for (int i = 1; i != x.size(); ++i) expected_c += x.get(i);

//     TTS_EQUAL(eve::count_true[eve::iota(eve::as<T>()) > 0](mmask), expected_c);

//     if constexpr (x.size() >= 2)
//     {
//       std::ptrdiff_t expected_cr = 0;
//       for (int i = x.size() - 1; i > x.size() - 3; --i) expected_cr += x.get(i);

//       TTS_EQUAL(eve::count_true[eve::keep_last(2)](mmask), expected_cr);
//     }
//   };

//   for (int i = 0; i != x.size(); ++i)
//   {
//     x.set(i, true);
//     test();

//     for (int j = i + 1; j < x.size(); ++j)
//     {
//       x.set(j, true);
//       test();
//       x.set(j, false);
//     }

//     x.set(i, false);
//   }
// };
