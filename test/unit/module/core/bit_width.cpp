//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of bit_width on wide", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::bit_width(T()), T);
  TTS_EXPR_IS(eve::bit_width(v_t()), v_t);
};

//==================================================================================================
// bit_width(wide) tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_width(wide) on unsigned integrals",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, U const& t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::bit_width(a0), map([](auto e) -> v_t { return std::bit_width(e); }, a0));
  TTS_EQUAL(eve::bit_width[t](a0), eve::if_else(t, eve::bit_width(a0), a0));
};

//==================================================================================================
// bit_width(scalar) tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_width(wide) on unsigned integrals",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  for( int i = 0; i != T::size(); ++i )
  {
    auto a = a0.get(i);
    TTS_EQUAL(eve::bit_width(a), v_t(std::bit_width(a)));
  }
};
