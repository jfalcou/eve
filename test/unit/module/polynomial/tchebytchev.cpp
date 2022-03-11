//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/polynomial.hpp>
#include <boost/math/special_functions/chebyshev.hpp>

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
//  TTS_EXPR_IS( eve::tchebytchev(i_t(), v_t())  , v_t);
  TTS_EXPR_IS( eve::tchebytchev(wi_t(), v_t())  , T);

};

//==================================================================================================
//== tchebytchev tests
//==================================================================================================
EVE_TEST( "Check behavior of tchebytchev on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::between(-1.0, 1.0), eve::test::as_integer(eve::test::ramp(0)))
        )
  <typename T, typename I>(T const& a0,I const & )
{
// using v_t = eve::element_type_t<T>;
  auto eve__tchebytchev  =  [](uint32_t n, auto x) { return eve::tchebytchev(n, x); };
  for(unsigned int n=0; n < 10; ++n)
  {
    std::cout << "n = " << n << std::endl;
    auto boost_tchebytchev =  [&](auto i, auto e) { return boost::math::chebyshev_t(i, e); };
    TTS_ULP_EQUAL(eve__tchebytchev(n, a0), map(boost_tchebytchev, n, a0), 32);
    if(n == 3)
    {
      std::cout << std::setprecision(10) << a0 << std::endl;
      std::cout << std::setprecision(10) << eve::ulpdist(eve__tchebytchev(n, a0), a0*(4*eve::sqr(a0)-3)) << std::endl;
      std::cout << std::setprecision(10) << eve::ulpdist(map(boost_tchebytchev, n, a0), a0*(4*eve::sqr(a0)-3)) << std::endl;
      TTS_ULP_EQUAL(eve__tchebytchev(n, a0), a0*(4*eve::sqr(a0)-3), 32);
      TTS_ULP_EQUAL(map(boost_tchebytchev, n, a0), a0*(4*eve::sqr(a0)-3), 32);
    }
  }
//   auto boost_tchebytchev =  [&](auto i, auto) { return boost::math::chebyshev_t(i0.get(i), a0.get(i)); };
//   TTS_ULP_EQUAL(eve__tchebytchev(i0    , a0), T(boost_tchebytchev), 16);
//   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
//   {
//     auto boost_tchebytchev2 =  [&](auto i, auto) { return boost::math::chebyshev_t(i0.get(i), a0.get(j)); };
//     TTS_ULP_EQUAL(eve__tchebytchev(i0 , a0.get(j)), T(boost_tchebytchev2(i0.get(i), a0.get(j)), 32);
//   }
//   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
//   {
//     for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
//     {
//       TTS_ULP_EQUAL(eve__tchebytchev(i0.get(j) , a0.get(n)), v_t(boost::math::chebyshev_t(i0.get(j), a0.get(n))), 32);
//     }
//   }
};


// //==================================================================================================
// //== tchebytchev diff tests
// //==================================================================================================
// EVE_TEST( "Check behavior of diff tchebytchev on wide"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::between(-1.0, 1.0), eve::test::as_integer(eve::test::ramp(0)))
//         )
//   <typename T, typename I>(T const& a0,I const & i0)
// {
//   auto boost_tchebderiv = [](auto n,  auto x){return boost::math::chebytchev_t_prime(n+1, x); };

//   using v_t = eve::element_type_t<T>;
//   auto eve__tchebytchevv  =  [](auto n, auto x) { return eve::diff(eve::tchebytchev)(n, x); };
//   for(unsigned int n=0; n < 5; ++n)
//   {
//     auto boost_tchebytchev =  [&](auto i, auto) { return boost_tchebderiv(n, a0.get(i)); };
//     TTS_ULP_EQUAL(eve__tchebytchevv(n, a0), T(boost_tchebytchev), 32);
//   }
//   auto boost_tchebytchevv =  [&](auto i, auto) { return boost_tchebderiv(i0.get(i), a0.get(i)); };
//   TTS_ULP_EQUAL(eve__tchebytchevv(i0    , a0), T(boost_tchebytchevv), 32);
//   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
//   {
//     auto boost_tchebytchev2 =  [&](auto i, auto) { return boost_tchebderiv(i0.get(i), a0.get(j)); };
//     TTS_ULP_EQUAL(eve__tchebytchevv(i0 , a0.get(j)), T(boost_tchebytchev2), 48);
//   }
//   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
//   {
//     for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
//     {
//       TTS_ULP_EQUAL(eve__tchebytchevv(i0.get(j) , a0.get(n)), v_t(boost_tchebderiv(i0.get(j), a0.get(n))), 100);
//     }
//   }
// };
