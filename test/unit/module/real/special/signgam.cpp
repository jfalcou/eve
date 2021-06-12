//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/function/all.hpp>
#include <eve/function/signgam.hpp>
#include <eve/function/ulpdist.hpp>
#include <type_traits>
#include <cmath>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/platform.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of signgam"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::signgam(T())  , T);
  TTS_EXPR_IS( eve::signgam(v_t()), v_t);
};

//==================================================================================================
// signgam  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of signgam on wide"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as_<T>)
{
  using eve::signgam;
  using eve::as;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(signgam(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(signgam(eve::inf(eve::as<T>()))  , eve::one(eve::as<T>()) );
    TTS_IEEE_EQUAL(signgam(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_EQUAL(signgam(T(0.5)), T(1) );
  TTS_IEEE_EQUAL(signgam(T(-35)), eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(signgam(T( 0 )), T(1) );
  TTS_IEEE_EQUAL(signgam(T(-0.)), T(-1) );
  TTS_IEEE_EQUAL(signgam(T( 1 )), T(1) );
  TTS_IEEE_EQUAL(signgam(T( 2 )), T(1) );
  TTS_IEEE_EQUAL(signgam(T( 3 )), T(1) );
  TTS_IEEE_EQUAL(signgam(T( 5 )), T(1) );
  TTS_IEEE_EQUAL(signgam(T( -1.1 )), T(1) );
  TTS_IEEE_EQUAL(signgam(T( -2.1 )), T(-1) );
  TTS_IEEE_EQUAL(signgam(T( -3.1 )), T(1) );
  TTS_IEEE_EQUAL(signgam(T( -4.1 )), T(-1) );
  TTS_IEEE_EQUAL(signgam(T( -5.1 )), T(1) );
};
