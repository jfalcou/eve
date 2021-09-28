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
#include <eve/function/all.hpp>
#include <eve/function/digamma.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <type_traits>
#include <cmath>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include <eve/detail/diff_div.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of digamma"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::digamma(T())  , T);
  TTS_EXPR_IS( eve::digamma(v_t()), v_t);
};

//==================================================================================================
// digamma  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of digamma on wide"
              , eve::test::simd::ieee_floats
              )
  <typename T>(eve::as<T> )
{
  using eve::digamma;
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(digamma(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(digamma(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(digamma(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }
  auto ulp = 2.0;
  TTS_ULP_EQUAL(digamma(T(0.125)), T(-8.3884926632958548678027429230863430000514460424495L), ulp);
  TTS_ULP_EQUAL(digamma(T(0.5)), T(-1.9635100260214234794409763329987555671931596046604L), ulp);
  TTS_ULP_EQUAL(digamma(T(1)), T(-0.57721566490153286060651209008240243104215933593992L), ulp);
  TTS_ULP_EQUAL(digamma(T(1.5)), T(0.036489973978576520559023667001244432806840395339566L), ulp * 40);
  TTS_ULP_EQUAL(digamma(T(1.5) - T(1)/32), T(0.00686541147073577672813890866512415766586241385896200579891429L), ulp * 100);
  TTS_ULP_EQUAL(digamma(T(2)), T(0.42278433509846713939348790991759756895784066406008L), ulp);
  TTS_ULP_EQUAL(digamma(T(8)), T(2.0156414779556099965363450527747404261006978069172L), ulp);
  TTS_ULP_EQUAL(digamma(T(12)), T(2.4426616799758120167383652547949424463027180089374L), ulp);
  TTS_ULP_EQUAL(digamma(T(22)), T(3.0681430398611966699248760264450329818421699570581L), ulp);
  TTS_ULP_EQUAL(digamma(T(50)), T(3.9019896734278921969539597028823666609284424880275L), ulp);
  TTS_ULP_EQUAL(digamma(T(500)), T(6.2136077650889917423827750552855712637776544784569L), ulp);
  TTS_ULP_EQUAL(digamma(T(3.193317413330078125)), T(digamma(3.193317413330078125)), ulp);
  TTS_ULP_EQUAL(digamma(T(3.193317413330078125)), T(9.963879482071649e-01), ulp);
  //
  // negative values:
  //
  TTS_ULP_EQUAL(digamma(T(-0.125)), T(7.1959829284523046176757814502538535827603450463013L), ulp);
  TTS_ULP_EQUAL(digamma(T(-10.125)), T(9.9480538258660761287008034071425343357982429855241L), ulp);
  TTS_ULP_EQUAL(digamma(T(-10.875)), T(-5.1527360383841562620205965901515879492020193154231L), ulp);
  TTS_ULP_EQUAL(digamma(T(-1.5)), T(0.70315664064524318722569033366791109947350706200623L), ulp);
};

EVE_TEST( "Check behavior of digamma on wide"
        , eve::test::simd::ieee_floats
        , eve::test::generate(eve::test::randoms(0.4, 4.0))
        )
<typename T>(T const& a0)
{
  TTS_ULP_EQUAL(eve::digamma(a0), T(map(eve::digamma, a0)), 2);
};
