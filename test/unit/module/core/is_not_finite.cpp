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
TTS_CASE_TPL( "Check return types of eve::is_not_finite(simd)"
              , eve::test::simd::all_types
              )
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_not_finite(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_not_finite(v_t())                  , logical<v_t> );
};

TTS_CASE_WITH( "Check behavior of eve::is_not_finite(simd)"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::ramp(0)
                              , tts::logicals(0, 3))
        )
<typename T, typename M>(T const& a0,  M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_not_finite(a0), map([](auto e) -> eve::logical<v_t> { return  e - e != 0; }, a0));
  TTS_EQUAL(eve::is_not_finite[t](a0), eve::if_else(t, eve::is_not_finite(a0), eve::false_(eve::as(a0))));
};

//==================================================================================================
// Test cases values
//==================================================================================================
TTS_CASE_TPL( "Check corner-cases behavior of eve::is_not_finite on wide"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T> tgt)
{
  using eve::as;

  auto cases = tts::limits(tgt);
  TTS_EQUAL( eve::is_not_finite(cases.nan    ) , eve::true_ (as<T>()));
  TTS_EQUAL( eve::is_not_finite(-cases.nan   ) , eve::true_ (as<T>()));
  TTS_EQUAL( eve::is_not_finite(cases.minf   ) , eve::true_ (as<T>()));
  TTS_EQUAL( eve::is_not_finite(cases.inf    ) , eve::true_ (as<T>()));
  TTS_EQUAL( eve::is_not_finite(cases.zero   ) , eve::false_(as<T>()));
  TTS_EQUAL( eve::is_not_finite(cases.mzero  ) , eve::false_(as<T>()));
  TTS_EQUAL( eve::is_not_finite(cases.valmin ) , eve::false_(as<T>()));
  TTS_EQUAL( eve::is_not_finite(cases.valmax ) , eve::false_(as<T>()));
};
