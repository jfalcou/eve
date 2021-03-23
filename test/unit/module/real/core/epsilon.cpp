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
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/eps.hpp>
#include <eve/function/epsilon.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of epsilon"
            , eve::test::simd::all_types

            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::epsilon(T())  , T);
  TTS_EXPR_IS( eve::epsilon(v_t()), v_t);
};



//==================================================================================================
// epsilon  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of epsilon on ieee real wide"
        , eve::test::simd::ieee_reals

        )
<typename T>(eve::as_<T>)
{
  using eve::as;
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::epsilon(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::epsilon(eve::inf(eve::as<T>())),  eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::epsilon(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  TTS_ULP_EQUAL(eve::epsilon(T(1)), eve::eps(as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::epsilon(T(0)), eve::mindenormal(as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::epsilon(T(10)), 8*eve::eps(as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::epsilon(T(5)),  4*eve::eps(as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::epsilon(T(2)),  2*eve::eps(as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::epsilon(T(1.5)),  eve::eps(as<T>()), 0.5);
};

EVE_TEST( "Check behavior of saturated(epsilon) on integral wide"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  using eve::as;
  TTS_EQUAL( eve::epsilon(a0), T(1));
};
