//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <boost/math/special_functions/gegenbauer.hpp>
#include <eve/module/polynomial.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of gegenbauer on wide"
        , eve::test::simd::ieee_reals

        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::gegenbauer(i_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::gegenbauer(wi_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::gegenbauer(i_t(), T(), v_t())  , T);
  TTS_EXPR_IS( eve::gegenbauer(wi_t(), T(), v_t())  , T);
};

//==================================================================================================
//== gegenbauer tests
//==================================================================================================
EVE_TEST( "Check behavior of gegenbauer on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::between(0.0, 1.0), eve::test::as_integer(eve::test::ramp(0)))
        )
  <typename T, typename I>(T const& a0,I const & i0)
{
  using v_t = eve::element_type_t<T>;
  v_t l = v_t(-3)/v_t(8);
  auto eve__gegenbauerv  =  [l](auto n, auto x) { return eve::gegenbauer(n, l, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_gegenbauer =  [&](auto i, auto) { return boost::math::gegenbauer(n, l, a0.get(i)); };
    TTS_ULP_EQUAL(eve__gegenbauerv(n, a0), T(boost_gegenbauer), 256);
  }
  auto boost_gegenbauerv =  [&](auto i, auto) { return boost::math::gegenbauer(i0.get(i), l, a0.get(i)); };
  TTS_ULP_EQUAL(eve__gegenbauerv(i0    , a0), T(boost_gegenbauerv), 256);
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_gegenbauer2 =  [&](auto i, auto) { return boost::math::gegenbauer(i0.get(i), l, a0.get(j)); };
    TTS_ULP_EQUAL(eve__gegenbauerv(i0 , a0.get(j)), T(boost_gegenbauer2), 256);
  }
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_ULP_EQUAL(eve__gegenbauerv(i0.get(j) , a0.get(n)), v_t(boost::math::gegenbauer(i0.get(j), l, a0.get(n))), 256);
    }
  }
};
