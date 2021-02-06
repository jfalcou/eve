//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/all.hpp>

#include <eve/conditional.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::all return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::all(eve::logical<T>())) , bool);
  TTS_EXPR_IS( (eve::all(T()))               , bool);
}

TTS_CASE_TPL("Check eve::all behavior on arithmetic", EVE_TYPE)
{
  TTS_EXPECT    ( (eve::all(T{1})) );
  TTS_EXPECT_NOT( (eve::all(T{0})) );

  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_nans )
    {
      TTS_EXPECT(eve::all(eve::nan(eve::as<T>())));
    }

    TTS_EXPECT_NOT(eve::all(T(-0.)));
  }

#if defined(EVE_SIMD_TESTS)
  for(int j=0; j < EVE_CARDINAL; ++j)
  {
    T rhs1,rhs2, rhs3, rhs4;

    for(int i=0; i< EVE_CARDINAL; ++i)
    {
      rhs1.set(i, i >= j ? 0 : 1);
      rhs2.set(i, i <= j ? 0 : 1);
      rhs3.set(i, i == j ? 0 : 1);
      rhs4.set(i, i == j ? 1 : 0);
    }

    TTS_EXPECT_NOT(eve::all(rhs1));
    TTS_EXPECT_NOT(eve::all(rhs2));
    TTS_EXPECT_NOT(eve::all(rhs3));

    if constexpr(EVE_CARDINAL == 1) TTS_EXPECT(eve::all(rhs4));
    else                        TTS_EXPECT_NOT(eve::all(rhs4));
  }
#endif
}

TTS_CASE_TPL("Check eve::all behavior on logical", EVE_TYPE)
{
  TTS_EXPECT    (eve::all(eve::true_(eve::as<T>())));
  TTS_EXPECT_NOT(eve::all(eve::false_(eve::as<T>())));
}

#if defined(EVE_SIMD_TESTS)

TTS_CASE_TPL("Check eve::all[ignore]", EVE_TYPE)
{
  // complete
  {
    eve::logical<T> mask(true);

    TTS_EXPECT(eve::all[eve::ignore_none](mask));

    mask = eve::logical<T>{false};
    TTS_EXPECT(eve::all[eve::ignore_all](mask));
  }

  // some special cases
  {
    eve::logical<T> mask(true);

    TTS_EXPECT(eve::all[eve::ignore_first(1)](mask));
    TTS_EXPECT(eve::all[eve::ignore_last(1)](mask));

    mask.set(0, false);
    TTS_EXPECT(eve::all[eve::ignore_first(1)](mask));
    TTS_EXPECT(eve::all[eve::ignore_last(T::static_size)](mask));
    TTS_EXPECT_NOT(eve::all[eve::ignore_last(T::static_size - 1)](mask));
  }

  // ignore_first, keep_last
  {
    eve::logical<T> mask(true);

    for(int i = 0; i != T::static_size; ++i )
    {
      TTS_EXPECT(eve::all[eve::ignore_first(i)](mask));
      mask.set(i, false);
      TTS_EXPECT_NOT(eve::all[eve::ignore_first(i)](mask));
      TTS_EXPECT(eve::all[eve::ignore_first(i + 1)](mask));

      TTS_EXPECT_NOT(eve::all[eve::keep_last(T::static_size - i)](mask));
      TTS_EXPECT(eve::all[eve::keep_last(T::static_size - i - 1)](mask));
    }
  }

  // ignore_last
  {
    eve::logical<T> mask(true);

    for(int i = 0; i != T::static_size; ++i )
    {
      TTS_EXPECT(eve::all[eve::ignore_last(i)](mask));
      mask.set(T::static_size - i - 1, false);
      TTS_EXPECT_NOT(eve::all[eve::ignore_last(i)](mask));
      TTS_EXPECT(eve::all[eve::ignore_last(i + 1)](mask));

      TTS_EXPECT_NOT(eve::all[eve::keep_first(T::static_size - i)](mask));
      TTS_EXPECT(eve::all[eve::keep_first(T::static_size - i - 1)](mask));
    }
  }

  // ignore_extrema_, keep_between
  {
    for (int i = 0; i < T::static_size + 1; ++i)
    {
      for (int j = T::static_size - i; j ; --j)
      {
        eve::logical<T> mask([&](int k, int) { return (k >= i) && (T::static_size - k) > j; });
        TTS_EXPECT(eve::all[eve::ignore_extrema_(i, j)](mask));

        if (i + j == T::static_size) continue;

        mask.set(i, false);

        TTS_EXPECT_NOT(eve::all[eve::ignore_extrema_(i, j)](mask));
        TTS_EXPECT(eve::all[eve::ignore_extrema_(i + 1, j)](mask));

        TTS_EXPECT_NOT(eve::all[eve::keep_between(i, T::static_size - j)](mask));
        TTS_EXPECT(eve::all[eve::keep_between(i + 1, T::static_size - j)](mask));

        mask.set(i, true);

        mask.set(T::static_size - j - 1, false);
        TTS_EXPECT_NOT(eve::all[eve::ignore_extrema_(i, j)](mask));
        TTS_EXPECT(eve::all[eve::ignore_extrema_(i, j + 1)](mask));

        TTS_EXPECT_NOT(eve::all[eve::keep_between(i, T::static_size - j)](mask));
        TTS_EXPECT(eve::all[eve::keep_between(i, T::static_size - j - 1)](mask));
      }
    }
  }
}

#endif
