//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/special.hpp>
#include <eve/concept/value.hpp>
#include <type_traits>
#include <cmath>
#include <eve/platform.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of erfc"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::erfc(T())  , T);
  TTS_EXPR_IS( eve::erfc(v_t()), v_t);
};

//==================================================================================================
// erfc  tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of erfc on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-10000.0, 10000.0))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  using eve::erfc;
  using eve::as;
  TTS_ULP_EQUAL( erfc(a0),  map([&](auto e) -> v_t{ return std::erfc(e); }, a0), 30);
  TTS_ULP_EQUAL(erfc(T(0.5)), T(std::erfc(v_t(0.5))), 2.0 );
  TTS_ULP_EQUAL(erfc(T(-35)), T(std::erfc(v_t(-35))), 0.5);
  TTS_ULP_EQUAL(erfc(T(eve::smallestposval(as<T>()))), T(std::erfc(eve::smallestposval(as<v_t>()))), 2.0);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(erfc(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(erfc(eve::inf(eve::as<T>()))  , eve::zero(eve::as<T>()) );
    TTS_IEEE_EQUAL(erfc(eve::minf(eve::as<T>())) ,T(2) );
  }
  TTS_ULP_EQUAL(erfc(T( 0 )), eve::one(eve::as<T>()), 1 );
  TTS_ULP_EQUAL(erfc(T(-0.)), eve::one(eve::as<T>()), 1  );
  TTS_EXPECT(eve::all(eve::is_positive(erfc(T(eve::inf(eve::as<T>()))))));
};
