//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

#include <eve/wide.hpp>


TTS_CASE_TPL( "Check behavior of identity swizzle", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = kumi::tuple<std::int8_t,T,double>;

  eve::wide<s_t> data = [](auto i, auto){ return s_t{ static_cast<std::int8_t>(65+i)
                                                    , static_cast<T>(i + 1)
                                                    , 1.5*(1+i)
                                                    };
                                            };

  eve::wide<s_t> expected([&](int i, int size) { return data.get(size - i - 1); });
  TTS_EQUAL(eve::reverse(data), expected);
  TTS_EQUAL(eve::shuffle(data, eve::as_pattern([](auto i, auto c) { return c-i-1;})), expected);
};
