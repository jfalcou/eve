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
#include <eve/constant/valmax.hpp>
#include <eve/constant/zero.hpp>

EVE_TEST_TYPES( "Check behavior of arithmetic as_value", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  e_t max_value = std::numeric_limits<e_t>::max();

  {
    T expected{max_value};
    T actual = eve::as_value(eve::valmax, eve::as<T>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(max_value, eve::as<T>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(expected, eve::as<T>{});
    TTS_EQUAL(expected, actual);
  }

  {
    e_t expected{max_value};
    e_t actual = eve::as_value(eve::valmax, eve::as<e_t>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(max_value, eve::as<e_t>{});
    TTS_EQUAL(expected, actual);
  }

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
    e_t expected{0};
    e_t actual = eve::as_value(eve::zero, eve::as<e_t>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(0, eve::as<e_t>{});
    TTS_EQUAL(expected, actual);
    actual = eve::as_value(expected, eve::as<e_t>{});
    TTS_EQUAL(expected, actual);
  }
};

EVE_TEST_TYPES( "Check behavior of logical as_value", eve::test::simd::restricted::all_types)
<typename T>(eve::as<T>)
{
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
