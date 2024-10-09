//======================================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//======================================================================================================================
#include "test.hpp"
#include <eve/module/math.hpp>
#include <cmath>

//======================================================================================================================
// Types tests
//======================================================================================================================
TTS_CASE_TPL("Check return types of acosd", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::acosd(T())                        , T   );
  TTS_EXPR_IS(eve::acosd(v_t())                      , v_t );
  TTS_EXPR_IS(eve::acosd[eve::raw](T())              , T   );
  TTS_EXPR_IS(eve::acosd[eve::raw](v_t())            , v_t );
  TTS_EXPR_IS(eve::acosd[T() < 0](T())               , T   );
  TTS_EXPR_IS(eve::acosd[v_t() < 0](v_t())           , v_t );
  TTS_EXPR_IS(eve::acosd[eve::raw][T() < 0](T())     , T   );
  TTS_EXPR_IS(eve::acosd[eve::raw][v_t() < 0](v_t()) , v_t );
  TTS_EXPR_IS(eve::acosd[T() < 0][eve::raw](T())     , T   );
  TTS_EXPR_IS(eve::acosd[v_t() < 0][eve::raw](v_t()) , v_t );
};

//======================================================================================================================
// acosd  tests
//======================================================================================================================
TTS_CASE_WITH("Check behavior of acosd", eve::test::simd::ieee_reals, tts::generate(tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::acosd(a0), tts::map([](auto e) -> v_t { return eve::radindeg(std::acos(e)); }, a0), 2);
};

TTS_CASE_WITH("Check behavior of acosd[raw]", eve::test::simd::ieee_reals, tts::generate(tts::randoms(1.-1e-6, 1.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_ABSOLUTE_EQUAL( eve::acosd[eve::raw](a0), tts::map([](auto e) -> v_t { return eve::radindeg(std::acos(e)); }, a0)
                    , 200 * eve::eps(eve::as<v_t>())
                    );
  TTS_ABSOLUTE_EQUAL( eve::acosd[eve::raw](-a0), tts::map([](auto e) -> v_t { return eve::radindeg(std::acos(e)); }, -a0)
                    , 200 * eve::eps(eve::as<v_t>())
                    );
};

//======================================================================================================================
// Tests for masked acosd
//======================================================================================================================
TTS_CASE_WITH ( "Check behavior of eve::masked(eve::acosd)(eve::wide)"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3))
              )
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::acosd[mask](a0),eve::if_else(mask, eve::acosd(a0), a0));
};
