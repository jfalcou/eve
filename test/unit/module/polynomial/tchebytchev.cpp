//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/polynomial.hpp>
#include <boost/math/special_functions/tchebytchev.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of tchebytchev on wide"
        , eve::test::simd::ieee_reals

        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::tchebytchev(i_t(), T())  , T);
  TTS_EXPR_IS( eve::tchebytchev(wi_t(), T())  , T);
  TTS_EXPR_IS( eve::tchebytchev(i_t(), v_t())  , v_t);
  TTS_EXPR_IS( eve::tchebytchev(wi_t(), v_t())  , T);

};

//==================================================================================================
//== tchebytchev tests
//==================================================================================================
EVE_TEST( "Check behavior of tchebytchev on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::between(-1.0, 1.0), eve::test::as_integer(eve::test::ramp(0)))
        )
  <typename T, typename I>(T const& a0,I const & i0)
{
 using v_t = eve::element_type_t<T>;
  auto eve__tchebytchevv  =  [](auto n, auto x) { return eve::tchebytchev(n, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_tchebytchev =  [&](auto i, auto) { return boost::math::tchebytchev(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve__tchebytchevv(n, a0), T(boost_tchebytchev), 16);
  }
  auto boost_tchebytchevv =  [&](auto i, auto) { return boost::math::tchebytchev(i0.get(i), a0.get(i)); };
  TTS_ULP_EQUAL(eve__tchebytchevv(i0    , a0), T(boost_tchebytchevv), 16);
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_tchebytchev2 =  [&](auto i, auto) { return boost::math::tchebytchev(i0.get(i), a0.get(j)); };
    TTS_ULP_EQUAL(eve__tchebytchevv(i0 , a0.get(j)), T(boost_tchebytchev2), 32);
  }
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_ULP_EQUAL(eve__tchebytchevv(i0.get(j) , a0.get(n)), v_t(boost::math::tchebytchev(i0.get(j), a0.get(n))), 32);
    }
  }
};


//==================================================================================================
//== tchebytchev diff tests
//==================================================================================================
EVE_TEST( "Check behavior of diff tchebytchev on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::between(-1.0, 1.0), eve::test::as_integer(eve::test::ramp(0)))
        )
  <typename T, typename I>(T const& a0,I const & i0)
{
  auto boost_hermderiv = [](auto n,  auto x){return 2*x*boost::math::tchebytchev(n, x)-boost::math::tchebytchev(n+1, x); };

  using v_t = eve::element_type_t<T>;
  auto eve__tchebytchevv  =  [](auto n, auto x) { return eve::diff(eve::tchebytchev)(n, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_tchebytchev =  [&](auto i, auto) { return boost_hermderiv(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve__tchebytchevv(n, a0), T(boost_tchebytchev), 32);
  }
  auto boost_tchebytchevv =  [&](auto i, auto) { return boost_hermderiv(i0.get(i), a0.get(i)); };
  TTS_ULP_EQUAL(eve__tchebytchevv(i0    , a0), T(boost_tchebytchevv), 32);
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_tchebytchev2 =  [&](auto i, auto) { return boost_hermderiv(i0.get(i), a0.get(j)); };
    TTS_ULP_EQUAL(eve__tchebytchevv(i0 , a0.get(j)), T(boost_tchebytchev2), 48);
  }
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_ULP_EQUAL(eve__tchebytchevv(i0.get(j) , a0.get(n)), v_t(boost_hermderiv(i0.get(j), a0.get(n))), 100);
    }
  }
};
