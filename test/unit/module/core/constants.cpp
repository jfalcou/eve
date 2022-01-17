//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/platform.hpp>
#include <eve/logical.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>

EVE_TEST_TYPES("Check basic constants behavior"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  using eve::as;
  using elt_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::allbits(as<T>()), eve::bit_not(T(0)));
  TTS_EQUAL(eve::true_(as<T>()), eve::as_logical_t<T>(1));
  TTS_EQUAL(eve::false_(as<T>()), eve::as_logical_t<T>(0));
  TTS_EQUAL(eve::one(as<T>()), T(1));
  TTS_EQUAL(eve::mone(as<T>()), T(-1));
  TTS_EQUAL(eve::zero(as<T>()), T(0));

  if constexpr(eve::floating_value < T>)
  {
    TTS_IEEE_EQUAL(eve::allbits(as<T>()), T(0.0/0.0));
    TTS_EQUAL(eve::mzero(as<T>()), T(-0));
    TTS_EQUAL(eve::half(as<T>()), T(0.5));
    TTS_EQUAL(eve::mhalf(as<T>()), T(-0.5));
    TTS_EXPECT(eve::all(eve::is_negative(eve::mzero(as<T>()))));
  }
  else if  constexpr(eve::integral_value < T>)
  {
    TTS_EQUAL(eve::allbits(as<T>()), T(elt_t(~0)));
  }
};
