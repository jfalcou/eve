//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <boost/math/special_functions/jacobi.hpp>
#include <eve/module/polynomial.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of jacobi on wide"
        , eve::test::simd::ieee_reals

        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::jacobi(i_t(), T())  , T);
  TTS_EXPR_IS( eve::jacobi(wi_t(), T())  , T);
  TTS_EXPR_IS( eve::jacobi(i_t(), v_t())  , v_t);
  TTS_EXPR_IS( eve::jacobi(wi_t(), v_t())  , T);

};

//==================================================================================================
//== jacobi tests
//==================================================================================================
EVE_TEST( "Check behavior of jacobi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::between(-1, 1), eve::test::as_integer(eve::test::ramp(0)))
        )
  <typename T, typename I>(T const& a0,I const & i0)
{
  using v_t = eve::element_type_t<T>;
  auto eve__jacobiv  =  [](auto n, auto x) { return eve::jacobi(n, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_jacobi =  [&](auto i, auto) { return boost::math::jacobi(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve__jacobiv(n, a0), T(boost_jacobi), 1024);
  }
  auto boost_jacobiv =  [&](auto i, auto) { return boost::math::jacobi(i0.get(i), a0.get(i)); };
  TTS_RELATIVE_EQUAL(eve__jacobiv(i0    , a0), T(boost_jacobiv), 0.01);
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_jacobi2 =  [&](auto i, auto) { return boost::math::jacobi(i0.get(i), a0.get(j)); };
    TTS_RELATIVE_EQUAL(eve__jacobiv(i0 , a0.get(j)), T(boost_jacobi2), 0.01);
  }
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_RELATIVE_EQUAL(eve__jacobiv(i0.get(j) , a0.get(n)), v_t(boost::math::jacobi(i0.get(j), a0.get(n))), 0.01);
    }
  }
};
