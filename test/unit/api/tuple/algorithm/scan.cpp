//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include <eve/module/core.hpp>
#include "test.hpp"


TTS_CASE_TPL( "Check behavior of scan", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = kumi::tuple<std::int8_t,T,double>;
  using w_t = eve::wide<s_t>;

  w_t x = [](auto i, auto) { return  s_t { static_cast<std::int8_t>(65+i)
                                          , static_cast<T>(i + 1)
                                          , 1.5*(1+i)
                                          };
                            };

  w_t expected = kumi::map(eve::scan, x);

  auto plus = [](auto a, auto b) {
    return kumi::map(eve::plus, a, b);
  };

  w_t actual_1 = eve::scan(x, plus, eve::zero);
  TTS_EQUAL(expected, actual_1);

  w_t actual_2 = eve::scan(x, plus, s_t{0, 0, 0});
  TTS_EQUAL(expected, actual_2);

  w_t actual_3 = eve::scan(x, plus, eve::zero(eve::as<w_t>{}));
  TTS_EQUAL(expected, actual_3);
};


TTS_CASE_TPL( "Check behavior of scan, same type", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = kumi::tuple<T,T,T>;
  using w_t = eve::wide<s_t>;

  w_t x = [](auto i, auto) { return  s_t {  (T)(i - 1)
                                          , (T)i
                                          , (T)(i + 1)
                                          };
                            };

  w_t expected = kumi::map(eve::scan, x);

  auto plus = [](auto a, auto b) {
    return kumi::map(eve::plus, a, b);
  };

  w_t actual_1 = eve::scan(x, plus, eve::zero);
  TTS_EQUAL(expected, actual_1);

  w_t actual_2 = eve::scan(x, plus, s_t{0, 0, 0});
  TTS_EQUAL(expected, actual_2);

  w_t actual_3 = eve::scan(x, plus, eve::zero(eve::as<w_t>{}));
  TTS_EQUAL(expected, actual_3);
};
