//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/constant/as_value.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/zero.hpp>

EVE_TEST_TYPES( "Check behavior of as_value for wides", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  {
    T expected{0};
    T actual = eve::as_value(eve::zero, eve::as<T>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(0, eve::as<T>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(expected, eve::as<T>{});
    TTS_EQUAL(expected, actual);
  }

  {
    using U = eve::logical<T>;
    U expected{true};
    U actual = eve::as_value(eve::true_, eve::as<U>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(true, eve::as<U>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(expected, eve::as<U>{});
    TTS_EQUAL(expected, actual);
  }

  {
    using U = eve::element_type_t<T>;
    U expected{0};
    U actual = eve::as_value(eve::zero, eve::as<U>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(0, eve::as<U>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(expected, eve::as<U>{});
    TTS_EQUAL(expected, actual);
  }

  {
    using U = eve::logical<eve::element_type_t<T>>;
    U expected{true};
    U actual = eve::as_value(eve::true_, eve::as<U>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(true, eve::as<U>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(expected, eve::as<U>{});
    TTS_EQUAL(expected, actual);
  }
};
