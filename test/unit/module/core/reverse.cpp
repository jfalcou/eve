//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

#include <eve/wide.hpp>

namespace {
//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::reverse", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::reverse(T()), T);
  TTS_EXPR_IS(eve::reverse(v_t()), v_t);

};

template <typename T>
void reverse_test(T x)
{
  auto frx =  [&](size_t i, size_t size) { return x.get(size - i - 1); };
  T expected(frx);
  TTS_EQUAL(eve::reverse(x), expected);
}

TTS_CASE_WITH( "Check behavior of reverse"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a)
{
  reverse_test(a);
};

TTS_CASE_TPL( "Check behavior of reverse with tuple", eve::test::scalar::all_types)
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

}
