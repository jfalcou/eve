//======================================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//======================================================================================================================
#include "test.hpp"
#include "std_proxy.hpp"
#include <eve/module/math.hpp>
#include <cmath>

//======================================================================================================================
// Types tests
//======================================================================================================================
TTS_CASE_TPL("Check return types of acospi", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::acospi(T())                        , T   );
  TTS_EXPR_IS(eve::acospi(v_t())                      , v_t );
  TTS_EXPR_IS(eve::acospi[eve::raw](T())              , T   );
  TTS_EXPR_IS(eve::acospi[eve::raw](v_t())            , v_t );
  TTS_EXPR_IS(eve::acospi[T() < 0](T())               , T   );
  TTS_EXPR_IS(eve::acospi[v_t() < 0](v_t())           , v_t );
  TTS_EXPR_IS(eve::acospi[eve::raw][T() < 0](T())     , T   );
  TTS_EXPR_IS(eve::acospi[eve::raw][v_t() < 0](v_t()) , v_t );
  TTS_EXPR_IS(eve::acospi[T() < 0][eve::raw](T())     , T   );
  TTS_EXPR_IS(eve::acospi[v_t() < 0][eve::raw](v_t()) , v_t );
};

//======================================================================================================================
// acospi  tests
//======================================================================================================================
TTS_CASE_WITH("Check behavior of acospi", eve::test::simd::ieee_reals_wf16, tts::generate(tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::acospi(a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(eve::radinpi(std_acos(e))); }, a0), 2);
};

//======================================================================================================================
// Tests for masked acospi
//======================================================================================================================
TTS_CASE_WITH ( "Check behavior of eve::masked(eve::acospi)(eve::wide)"
              , eve::test::simd::ieee_reals_wf16
              , tts::generate(tts::randoms(eve::valmin, eve::valmax), tts::logicals(0, 3))
              )
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::acospi[mask](a0),eve::if_else(mask, eve::acospi(a0), a0));
};

TTS_CASE_WITH("Check behavior of acospi on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1, 1), tts::randoms(0.9, 1)))
<typename T>(T const& a0, T const& a1)
{
   using eve::raw;
   auto prec = tts::prec<T>(0.005, 0.005);
   TTS_RELATIVE_EQUAL(eve::acospi(a0), eve::acospi[raw](a0), prec);
   TTS_RELATIVE_EQUAL(eve::acospi(a1), eve::acospi[raw](a1), prec);
   using eve::fast;
   auto prec1 = tts::prec<T>(0.00005, 0.00005);
   TTS_RELATIVE_EQUAL(eve::acospi(a0), eve::acospi[fast](a0), prec1);
   TTS_RELATIVE_EQUAL(eve::acospi(a1), eve::acospi[fast](a1), prec1);

};
