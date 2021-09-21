//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/significants.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of significants"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::significants(T(), int())  , T);
  TTS_EXPR_IS( eve::significants(v_t(), int()), v_t);
};

EVE_TEST_TYPES( "Check significants"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  TTS_IEEE_EQUAL(eve::significants(T(1.234567), 0), eve::nan(eve::as<T>()) );
  TTS_EQUAL(eve::significants(T(1.234567), 1), T(1.) );
  TTS_EQUAL(eve::significants(T(1.234567), 2), T(1.2) );
  TTS_EQUAL(eve::significants(T(1.234567), 3), T(1.23) );
  TTS_EQUAL(eve::significants(T(1.234567), 4), T(1.235) );
  TTS_EQUAL(eve::significants(T(0.01234567), 1),T(0.01) );
  TTS_EQUAL(eve::significants(T(0.01234567), 2),T(0.012) );
  TTS_EQUAL(eve::significants(T(0.01234567), 3),T(0.0123) );
  TTS_EQUAL(eve::significants(T(0.01234567), 4),T(0.01235) );

  TTS_IEEE_EQUAL(eve::significants(T(-1.234567), 0), eve::nan(eve::as<T>()) );
  TTS_EQUAL(eve::significants(T(-1.234567), 1), T(-1.) );
  TTS_EQUAL(eve::significants(T(-1.234567), 2), T(-1.2) );
  TTS_EQUAL(eve::significants(T(-1.234567), 3), T(-1.23) );
  TTS_EQUAL(eve::significants(T(-1.234567), 4), T(-1.235) );
  TTS_EQUAL(eve::significants(T(-0.01234567), 1),T(-0.01) );
  TTS_EQUAL(eve::significants(T(-0.01234567), 2),T(-0.012) );
  TTS_EQUAL(eve::significants(T(-0.01234567), 3),T(-0.0123) );
  TTS_EQUAL(eve::significants(T(-0.01234567), 4),T(-0.01235) );

  TTS_IEEE_EQUAL(eve::significants(T(0), 0), eve::nan(eve::as<T>()));
  TTS_EQUAL(eve::significants(T(0), 1), T(0) );
  TTS_EQUAL(eve::significants(T(0), 2), T(0) );
  TTS_EQUAL(eve::significants(T(0), 3), T(0) );
  TTS_EQUAL(eve::significants(T(0), 4), T(0) );


  TTS_IEEE_EQUAL(eve::significants(T(987654321), 0), eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::significants(T(987654321), 1), T(1000000000.0) );
  TTS_IEEE_EQUAL(eve::significants(T(987654321), 2), T(990000000.0) );
  TTS_IEEE_EQUAL(eve::significants(T(987654321), 3), T(988000000.0) );
  TTS_ULP_EQUAL (eve::significants(T(987654321), 4), T(987700000.0), 0.5);
  TTS_ULP_EQUAL (eve::significants(T(987654321), 5), T(987650000.0), 0.5);
  TTS_ULP_EQUAL (eve::significants(T(987654321), 6), T(987654000.0), 0.5);
};
