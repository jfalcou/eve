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
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of erf"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::erf(T())  , T);
  TTS_EXPR_IS( eve::erf(v_t()), v_t);
};

//==================================================================================================
// erf  tests
//==================================================================================================
EVE_TEST( "Check behavior of erf on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-10000.0, 10000.0))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  using eve::erf;
  using eve::as;
  TTS_ULP_EQUAL( erf(a0),  map([&](auto e) -> v_t{ return std::erf(e); }, a0), 2);
  auto derf = [](auto e){return 2*std::exp(-e*e)*v_t(.564189583547756286948);};
  TTS_ULP_EQUAL( eve::diff(erf)(a0),  map(derf, a0), 2);


  TTS_ULP_EQUAL(erf(T(0.5)), T(std::erf(v_t(0.5))), 1. );
  TTS_ULP_EQUAL(erf(T(-35)), T(std::erf(v_t(-35))), 0.5);
  TTS_ULP_EQUAL(erf(T(eve::smallestposval(as<T>()))), T(std::erf(eve::smallestposval(as<v_t>()))), 0.5);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(erf(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(erf(eve::inf(eve::as<T>()))  , eve::one(eve::as<T>()) );
    TTS_IEEE_EQUAL(erf(eve::minf(eve::as<T>())) , eve::mone(eve::as<T>()) );
  }
  TTS_IEEE_EQUAL(erf(T( 0 )), eve::zero(eve::as<T>())  );
  TTS_IEEE_EQUAL(erf(T(-0.)), eve::zero(eve::as<T>()) );
  TTS_EXPECT(eve::all(eve::is_negative(erf(T(-0.0 )))));
  TTS_EXPECT(eve::all(eve::is_positive(erf(T( 0.0 )))));
};
