//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of eve::nextafter"
              , eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t   = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::nextafter(T(), T())        , T);
  TTS_EXPR_IS(eve::nextafter(T(), v_t())      , T);
  TTS_EXPR_IS(eve::nextafter(v_t(), T())      , T);
  TTS_EXPR_IS(eve::nextafter(v_t(), v_t())    , v_t);
};

//==================================================================================================
// Tests for eve::nextafter
//==================================================================================================
TTS_CASE_WITH( "Check behavior of eve::nextafter"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              , tts::randoms(eve::valmin, eve::valmax)
                              )
        )
  <typename T>(T const& a0, T const & a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_real_value < v_t>)
  {
    auto n = [](auto e, auto f) -> v_t { return std::nextafter(e, f); };
    TTS_EQUAL(eve::nextafter(a0, a1)      , map(n, a0, a1) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::nextafter)(eve::nan(eve::as<T>())  , T(1)           ), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::nextafter)(T(1)           , eve::nan(eve::as<T>())  ), eve::nan(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(eve::nextafter(a0, a1), eve::if_else(a0 > a1, eve::dec(a0), eve::if_else(a0 < a1, eve::inc(a0), a0)));
  }
};
