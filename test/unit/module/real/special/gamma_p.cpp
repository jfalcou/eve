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
#include <eve/function/gamma_p.hpp>
#include <type_traits>
#include <cmath>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <boost/math/special_functions/gamma.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of gamma_p"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::gamma_p(T(), T())  , T);
  TTS_EXPR_IS( eve::gamma_p(T(), v_t()), T);
  TTS_EXPR_IS( eve::gamma_p(v_t(), T()), T);
  TTS_EXPR_IS( eve::gamma_p(v_t(), v_t()), v_t);
};

//==================================================================================================
// gamma_p  tests
//==================================================================================================
EVE_TEST( "Check behavior of gamma_p on wide"
        , eve::test::simd::ieee_reals //but there is a flaw in boost_gamma_p for double
        , eve::test::generate(eve::test::randoms(0.0, 100.0)
                             , eve::test::randoms(0.0, 5.0))
        )
<typename T>(T const& a0, T const& a1 )
{
  using v_t = eve::element_type_t<T>;
  using eve::gamma_p;
  TTS_ULP_EQUAL( eve::gamma_p(a0, a1),  map([&](auto e, auto f) -> v_t{ return boost::math::gamma_p(f, e); }, a0, a1), 4);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(gamma_p(eve::nan(eve::as<T>()), T(1))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(gamma_p(eve::inf(eve::as<T>()), T(1))  , T(1) );
  }
  TTS_ULP_EQUAL(gamma_p(T(0.0), T(1.0)), T(0), 0.5 );
  TTS_ULP_EQUAL(gamma_p(T(1.0), T(1.0)), eve::oneminus(eve::exp(T(-1))), 1);
  TTS_ULP_EQUAL(gamma_p(T(0.0), T(0.0)), T(1), 0.5 );
  TTS_ULP_EQUAL(gamma_p(T(0.25), T(1.0)), T(2.211992169285951e-01), 1 );
  TTS_ULP_EQUAL(gamma_p(T(0.25), T(0.25)), T(7.436779447314609e-01), 0.5 );
  TTS_ULP_EQUAL(gamma_p(T(1.0), T(0.25)), T(9.320788679898916e-01), 5.5 );
  TTS_ULP_EQUAL(gamma_p(T(0.25), T(2.0)), T(2.649902116074387e-02), 5.5 );
  TTS_ULP_EQUAL(gamma_p(T(0.25), T(2.25)), T( 1.460405690340118e-02), 0.5 );
  TTS_ULP_EQUAL(gamma_p(T(1.0), T(2.25)), T(2.015171022500710e-01), 3.5 );
  TTS_ULP_EQUAL(gamma_p(T(10.25), T(2.0)), T(9.996022281154329e-01), 2 );
  TTS_ULP_EQUAL(gamma_p(T(10.0), T(2.25)), T(9.991962820874968e-01), 0.5 );
  TTS_ULP_EQUAL(gamma_p(T(10.25), T(2.25)), T(9.993562658346851e-01), 0.5 );
  TTS_ULP_EQUAL(gamma_p(T(11.0), T(2.25)), T(9.996704204992496e-01), 0.5 );
  TTS_ULP_EQUAL(gamma_p(T(50.0), T(2.25)), T(1), 0 );
  TTS_ULP_EQUAL(gamma_p(T(10.0), T(4)), T(9.896639493240743e-01), 0.5 );
  TTS_ULP_EQUAL(gamma_p(T(10.1), T(4)), T(9.903947030847022e-01), 0.5 );
};
