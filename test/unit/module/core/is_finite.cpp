//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of eve::is_finite(simd)"
              , eve::test::simd::all_types
              )
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_finite(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_finite(v_t())                  , logical<v_t> );
};


//==================================================================================================
// Tests for eve::is_finite
//==================================================================================================
TTS_CASE_WITH( "Check behavior of eve::is_finite(simd) for IEEE"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::ramp(0), tts::logicals(0, 3))
        )
<typename T, typename M>(T  a0,  M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  a0 = eve::if_else(eve::is_eqz(a0), eve::inf(eve::as<v_t>()), eve::zero);
  TTS_EQUAL(eve::is_finite(a0), map([](auto e) -> eve::logical<v_t> { return e-e == 0; }, a0));
  TTS_EQUAL(eve::is_finite[t](a0), eve::if_else(t, eve::is_finite(a0), eve::false_(eve::as(a0))));
};

TTS_CASE_WITH( "Check behavior of eve::is_finite(simd) for integer"
        , eve::test::simd::integers
        , tts::generate ( tts::ramp(0), tts::logicals(0, 3))
        )
<typename T, typename M>(T  a0,  M const & t)
{
  using eve::detail::map;
  TTS_EQUAL(eve::is_finite(a0), eve::true_(eve::as(a0)));
  TTS_EQUAL(eve::is_finite[t](a0),  eve::if_else(t, eve::is_finite(a0), eve::false_(eve::as(a0))));
};

//==================================================================================================
// Test cases values
//==================================================================================================
TTS_CASE_TPL( "Check corner-cases behavior of eve::is_finite on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> tgt)
{
  using eve::as;
  auto cases= tts::limits(tgt);
  TTS_EQUAL( eve::is_finite(cases.nan    ) , eve::false_(as<T>()));
  TTS_EQUAL( eve::is_finite(-cases.nan   ) , eve::false_(as<T>()));
  TTS_EQUAL( eve::is_finite(cases.minf   ) , eve::false_(as<T>()));
  TTS_EQUAL( eve::is_finite(cases.inf    ) , eve::false_(as<T>()));
  TTS_EQUAL( eve::is_finite(cases.zero   ) , eve::true_(as<T>()));
  TTS_EQUAL( eve::is_finite(cases.mzero  ) , eve::true_(as<T>()));
  TTS_EQUAL( eve::is_finite(cases.valmin ) , eve::true_(as<T>()));
  TTS_EQUAL( eve::is_finite(cases.valmax ) , eve::true_(as<T>()));
};
