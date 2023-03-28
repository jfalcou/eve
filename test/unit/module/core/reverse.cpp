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
TTS_CASE_TPL("Check return types of eve::abs", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
//  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::reverse(T()), T);
  TTS_EXPR_IS(eve::reverse(T(), std::integral_constant<size_t, 1>()), T);
//   TTS_EXPR_IS(eve::reverse(v_t()), v_t);
//   TTS_EXPR_IS(eve::reverse(v_t(), std::integral_constant<size_t, 1>()), v_t);

};

template <typename T>
void reverse_test(T x)
{
//   auto frx =  [&](size_t i, size_t size) { return x.get(size - i - 1); };
//   auto fr  =  [](size_t i, size_t size) { return size - i - 1; };
//   T expected(frx);
//   TTS_EQUAL(eve::reverse(x), expected);
//   TTS_EQUAL(eve::shuffle(x, eve::as_pattern(fr)), expected);

  constexpr size_t S = eve::cardinal_v<T>;
  constexpr size_t N = S/4;
  auto frNx =  [&](size_t i, size_t S) { return x.get( ((i < N)  ? S-i-1 : ( (i > S-N-1) ? S-i-1 : i))); };
  auto frN  =  [ ](size_t i, size_t S) { return ((i < N)  ? S-i-1 : ( (i > S-N-1) ? S-i-1 : i)); };
//   for (size_t i = 0;  i < S; ++i) {
//     std::cout << "i = " << i << " S = " << S << "frN =  " << frN(i, S) << std::endl;
//  };
  T expectedN(frNx);
  TTS_EQUAL(eve::reverse(x, std::integral_constant<size_t, N>()), expectedN);
  TTS_EQUAL(eve::shuffle(x, eve::as_pattern(frN)), expectedN);
}

TTS_CASE_WITH( "Check behavior of reverse"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              , tts::logicals(0,3))
        )
<typename T, typename L>(T const& a, L const& l)
{
  reverse_test(a);
  reverse_test(l);
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
