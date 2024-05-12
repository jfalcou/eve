//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of log2"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::log2(T())  , T);
  TTS_EXPR_IS( eve::log2(v_t()), v_t);
};

//==================================================================================================
// log2  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of log2 on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(eve::eps, eve::valmax)
                             , tts::randoms(0.5, 2.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::log2(a0)      , map([](auto e) -> v_t { return std::log2(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::log2(a1)      , map([](auto e) -> v_t { return std::log2(e); }, a1), 2);


};

TTS_CASE_TPL( "Check return types of log2"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::log2(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log2(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log2(eve::mone(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log2(T( 0 ))         , eve::minf(eve::as<T>()));
  }

  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log2(eve::mindenormal(eve::as<T>())), T(std::log2(eve::mindenormal(eve::as<v_t>()))));
  }

  TTS_IEEE_EQUAL(eve::log2(T( 1)), T(0) );
  TTS_IEEE_EQUAL(eve::log2(T( 2)), T(1) );
  TTS_IEEE_EQUAL(eve::log2(T( 8)), T(3) );
  TTS_IEEE_EQUAL(eve::log2(T(64)), T(6) );

};
