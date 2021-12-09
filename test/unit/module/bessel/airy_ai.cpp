//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/airy_ai.hpp>
#include <eve/function/diff/airy_ai.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <boost/math/special_functions/airy.hpp>

EVE_TEST_TYPES( "Check return types of airy_ai"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::airy_ai(T(0)), T);
  TTS_EXPR_IS(eve::airy_ai(v_t(0)), v_t);
};

 EVE_TEST( "Check behavior of airy_ai on wide"
         , eve::test::simd::ieee_reals
         , eve::test::generate(eve::test::randoms(-20.0, 0.0),
                               eve::test::randoms(0.0, 20.0)
                              )
         )
   <typename T>(T a0, T a1)
{
  using v_t = eve::element_type_t<T>;
  v_t abstol = 1000*eve::eps(eve::as<v_t>());
  auto eve__airy_ai =  [](auto x) { return eve::airy_ai(x); };
  auto std__airy_ai =  [](auto x)->v_t { return boost::math::airy_ai(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__airy_ai(eve::minf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::inf(eve::as<v_t>())), v_t(0), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::minf(eve::as< T>())), eve::zero(eve::as< T>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::inf(eve::as< T>())),  T(0), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::nan(eve::as< T>())), eve::nan(eve::as< T>()), 0);
  }
  TTS_ULP_EQUAL(eve__airy_ai(v_t(1500)), std__airy_ai(v_t(1500)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(500)), std__airy_ai(v_t(500)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(10)),  std__airy_ai(v_t(10))  , 13.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(5)),  std__airy_ai(v_t(5))   , 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(2)),  std__airy_ai(v_t(2))   , 35.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(1.5)),std__airy_ai(v_t(1.5)) , 11.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(0.5)),std__airy_ai(v_t(0.5)) , 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(1)),  std__airy_ai(v_t(1))   , 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(0)),  v_t(0.355028053887817), 0.5);

  TTS_ULP_EQUAL(eve__airy_ai( T(1500)), T(std__airy_ai(v_t(1500))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(500)),  T(std__airy_ai(v_t(500)) ), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(10)) ,  T(std__airy_ai( v_t(10)) ), 13.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(5))  ,  T(std__airy_ai( v_t(5))  ), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(2))  ,  T(std__airy_ai( v_t(2))  ), 37.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(1.5)),  T(std__airy_ai( v_t(1.5))), 11.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(0.5)),  T(std__airy_ai( v_t(0.5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(1))  ,  T(std__airy_ai( v_t(1))  ), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(0))  ,  T(0.355028053887817), 0.5);

  TTS_ABSOLUTE_EQUAL(eve__airy_ai(v_t(-1500)), std__airy_ai(v_t(-1500)), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_ai(v_t(-500)), std__airy_ai(v_t(-500)), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_ai(v_t(-10)),  std__airy_ai(v_t(-10)), abstol);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(-5)),  std__airy_ai(v_t(-5))   , 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(-2)),  std__airy_ai(v_t(-2))   , 35.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(-1.5)),std__airy_ai(v_t(-1.5)) , 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(-0.5)),std__airy_ai(v_t(-0.5)) , 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(-1)),  std__airy_ai(v_t(-1))   , 10.0);


  TTS_ABSOLUTE_EQUAL(eve__airy_ai( T(-1500)), T(std__airy_ai(v_t(-1500))), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_ai( T(-500)),  T(std__airy_ai(v_t(-500)) ), abstol);
  TTS_ABSOLUTE_EQUAL(eve__airy_ai( T(-10)) ,  T(std__airy_ai( v_t(-10)) ), abstol);
  TTS_ULP_EQUAL(eve__airy_ai( T(-5))  ,  T(std__airy_ai( v_t(-5))  ), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(-2))  ,  T(std__airy_ai( v_t(-2))  ), 36.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(-1.5)),  T(std__airy_ai( v_t(-1.5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(-0.5)),  T(std__airy_ai( v_t(-0.5))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(-1))  ,  T(std__airy_ai( v_t(-1))  ), 10.0);


   TTS_ABSOLUTE_EQUAL(eve__airy_ai(a0), map(std__airy_ai, a0), 0.0001);
   TTS_RELATIVE_EQUAL(eve__airy_ai(a1), map(std__airy_ai, a1), 0.0001);

};

EVE_TEST( "Check behavior of diff(airy_ai) on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-20.0, 0.0),
                              eve::test::randoms(0.0, 20.0)
                             )
        )
  <typename T>(T a0, T a1)
{
  using v_t = eve::element_type_t<T>;
  v_t reltol = 50000000*eve::eps(eve::as<v_t>());
  auto eve__airy_ai =  [](auto x) { return eve::diff(eve::airy_ai)(x); };
  auto std__airy_ai =  [](auto x)->v_t { return boost::math::airy_ai_prime(x); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__airy_ai(eve::minf(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::inf(eve::as<v_t>())), eve::zero(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::minf(eve::as< T>())), eve::nan(eve::as< T>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::inf(eve::as< T>())), eve::zero(eve::as< T>()), 0);
    TTS_ULP_EQUAL(eve__airy_ai(eve::nan(eve::as< T>())), eve::nan(eve::as< T>()), 0);
  }
  TTS_ULP_EQUAL(eve__airy_ai(v_t(1500)), std__airy_ai(v_t(1500)), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(500)), std__airy_ai(v_t(500)), 10.0);

  TTS_ULP_EQUAL(eve__airy_ai(v_t(10)),  std__airy_ai(v_t(10)) , 50.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(5)),  std__airy_ai(v_t(5))   , 50.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(2)),  std__airy_ai(v_t(2))   , 50.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(1.5)),std__airy_ai(v_t(1.5)) , 50.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(0.5)),std__airy_ai(v_t(0.5)) , 51.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(1)),  std__airy_ai(v_t(1))   , 50.0);
  TTS_ULP_EQUAL(eve__airy_ai(v_t(0)),  v_t(-0.258819403792807), 0.5);

  TTS_ULP_EQUAL(eve__airy_ai( T(1500)), T(std__airy_ai(v_t(1500))), 10.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(500)),  T(std__airy_ai(v_t(500)) ), 10.0);

  TTS_ULP_EQUAL(eve__airy_ai( T(10)) ,  T(std__airy_ai( v_t(10)) ),  50.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(5))  ,  T(std__airy_ai( v_t(5))  ),  50.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(2))  ,  T(std__airy_ai( v_t(2))  ),  50.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(1.5)),  T(std__airy_ai( v_t(1.5))),  50.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(0.5)),  T(std__airy_ai( v_t(0.5))),  51.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(1))  ,  T(std__airy_ai( v_t(1))  ),  50.0);
  TTS_ULP_EQUAL(eve__airy_ai( T(0))  ,  T(-0.258819403792807), 0.5);

  TTS_RELATIVE_EQUAL(eve__airy_ai(v_t(-1500)), std__airy_ai(v_t(-1500)), reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai(v_t(-500)), std__airy_ai(v_t(-500)), reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai(v_t(-10)),  std__airy_ai(v_t(-10)) , reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai(v_t(-5)),  std__airy_ai(v_t(-5))   , reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai(v_t(-2)),  std__airy_ai(v_t(-2))   , reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai(v_t(-1.5)),std__airy_ai(v_t(-1.5)) , reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai(v_t(-0.5)),std__airy_ai(v_t(-0.5)) , reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai(v_t(-1)),  std__airy_ai(v_t(-1))   , reltol);


  TTS_ABSOLUTE_EQUAL(eve__airy_ai( T(-1500)), T(std__airy_ai(v_t(-1500))), reltol);
  TTS_ABSOLUTE_EQUAL(eve__airy_ai( T(-500)),  T(std__airy_ai(v_t(-500)) ), reltol);
  TTS_ABSOLUTE_EQUAL(eve__airy_ai( T(-10)) ,  T(std__airy_ai( v_t(-10)) ), reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai( T(-5))  ,  T(std__airy_ai( v_t(-5))  ), reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai( T(-2))  ,  T(std__airy_ai( v_t(-2))  ), reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai( T(-1.5)),  T(std__airy_ai( v_t(-1.5))), reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai( T(-0.5)),  T(std__airy_ai( v_t(-0.5))), reltol);
  TTS_RELATIVE_EQUAL(eve__airy_ai( T(-1))  ,  T(std__airy_ai( v_t(-1))  ), reltol);


  TTS_ABSOLUTE_EQUAL(eve__airy_ai(a0), map(std__airy_ai, a0), 0.0001);
  TTS_RELATIVE_EQUAL(eve__airy_ai(a1), map(std__airy_ai, a1), 0.0001);
};
