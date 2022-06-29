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
TTS_CASE_TPL( "Check return types of eve::is_infinite(simd)"
              , eve::test::simd::all_types
              )
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_infinite(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_infinite(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_infinite
//==================================================================================================
TTS_CASE_WITH( "Check behavior of eve::is_infinite(simd) integrals"
        , eve::test::simd::integers
        , tts::generate ( tts::ramp(0)
                              , tts::logicals(0, 3))
        )
<typename T, typename M>(T  a0,  M const & t)
{
  using eve::detail::map;
  TTS_EQUAL(eve::is_infinite(a0), eve::false_(eve::as(a0)));
  TTS_EQUAL(eve::is_infinite[t](a0), eve::if_else(t, eve::is_infinite(a0), eve::false_(eve::as(a0))));
};

TTS_CASE_WITH( "Check behavior of eve::is_infinite(simd) IEEE"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::ramp(0)
                              , tts::logicals(0, 3))
        )
<typename T, typename M>(T  a0,  M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  a0 = eve::if_else(eve::is_eqz(a0), eve::inf(eve::as<v_t>()), eve::zero);
  TTS_EQUAL(eve::is_infinite(a0), map([](auto e) -> eve::logical<v_t> { return e-e != 0 && e == e; }, a0));
  TTS_EQUAL(eve::is_infinite[t](a0), eve::if_else(t, eve::is_infinite(a0), eve::false_(eve::as(a0))));
};

//==================================================================================================
// Test cases values
//==================================================================================================
TTS_CASE_WITH( "Check corner-cases behavior of eve::is_infinite on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  using eve::as;
  TTS_EQUAL( eve::is_infinite(cases.nan    ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_infinite(-cases.nan   ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.minf   ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.inf    ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.zero   ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.mzero  ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.valmin ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.valmax ) , eve::false_(as<type>()));
};
