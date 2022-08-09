//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of bit_and", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::bit_and(T(), T()), T);
  TTS_EXPR_IS(eve::bit_and(T(), v_t()), T);
  TTS_EXPR_IS(eve::bit_and(v_t(), v_t()), v_t);

  using si_t = eve::as_integer_t<T, signed>;
  using ui_t = eve::as_integer_t<T, unsigned>;

  TTS_EXPR_IS(eve::bit_and(T(), si_t()), T);
  TTS_EXPR_IS(eve::bit_and(T(), ui_t()), T);

  using ssi_t = eve::as_integer_t<v_t, signed>;
  using sui_t = eve::as_integer_t<v_t, unsigned>;
  TTS_EXPR_IS(eve::bit_and(T(), ssi_t()), T);
  TTS_EXPR_IS(eve::bit_and(T(), sui_t()), T);
};

//==================================================================================================
//  bit_and tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_and on integral types",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& test)
{
  using eve::as;
  using eve::bit_and;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(bit_and(a0, a1), map([](auto e, auto f) -> v_t { return e & f; }, a0, a1));
  TTS_EQUAL(bit_and[test](a0, a1), eve::if_else(test, eve::bit_and(a0, a1), a0));
  TTS_EQUAL(bit_and[test](a0, a1, a2), eve::if_else(test, eve::bit_and(a0, a1, a2), a0));
};

TTS_CASE_WITH("Check behavior of bit_and on floating types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::as;
  using eve::bit_and;
  using eve::bit_cast;
  using eve::detail::map;
  using i_t = eve::as_integer_t<eve::element_type_t<T>, signed>;
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(
      bit_and(a0, a1),
      map([](auto e, auto f) -> v_t
          { return bit_cast(bit_cast(e, as(i_t())) & bit_cast(f, as(i_t())), as(v_t())); },
          a0,
          a1));
  auto test = a3 > eve::average(eve::valmin(as<T>()), eve::valmax(as<T>()));
  TTS_IEEE_EQUAL(bit_and[test](a0, a1), eve::if_else(test, eve::bit_and(a0, a1), a0));
  TTS_IEEE_EQUAL(bit_and[test](a0, a1, a2), eve::if_else(test, eve::bit_and(a0, a1, a2), a0));
};
