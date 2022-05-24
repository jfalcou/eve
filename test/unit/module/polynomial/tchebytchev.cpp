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

// //==================================================================================================
// //== Types tests
// //==================================================================================================
// EVE_TEST_TYPES( "Check return types of tchebytchev on wide"
//         , eve::test::simd::ieee_reals

//         )
// <typename T>(eve::as<T>)
// {
//   using v_t = eve::element_type_t<T>;
//   using wi_t = eve::as_integer_t<T>;
//   using i_t  = eve::as_integer_t<v_t>;
//   TTS_EXPR_IS( eve::tchebytchev(i_t(), T())  , T);
//   TTS_EXPR_IS( eve::tchebytchev(wi_t(), T())  , T);
//   TTS_EXPR_IS( eve::tchebytchev(i_t(), v_t())  , v_t);
//   TTS_EXPR_IS( eve::tchebytchev(wi_t(), v_t())  , T);

//   using eve::kind_1;
//   TTS_EXPR_IS( kind_1(eve::tchebytchev)(i_t(), T())  , T);
//   TTS_EXPR_IS( kind_1(eve::tchebytchev)(wi_t(), T())  , T);
//   TTS_EXPR_IS( kind_1(eve::tchebytchev)(i_t(), v_t())  , v_t);
//   TTS_EXPR_IS( kind_1(eve::tchebytchev)(wi_t(), v_t())  , T);

//   using eve::kind_2;
//   TTS_EXPR_IS( kind_2(eve::tchebytchev)(i_t(), T())  , T);
//   TTS_EXPR_IS( kind_2(eve::tchebytchev)(wi_t(), T())  , T);
//   TTS_EXPR_IS( kind_2(eve::tchebytchev)(i_t(), v_t())  , v_t);
//   TTS_EXPR_IS( kind_2(eve::tchebytchev)(wi_t(), v_t())  , T);
// };

// //==================================================================================================
// //== tchebytchev tests
// //==================================================================================================
// EVE_TEST( "Check behavior of tchebytchev on wide"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::between(-1.0, 1.0), eve::test::between(1.0, 10.0), eve::test::as_integer(eve::test::ramp(0)))
//         )
//   <typename T, typename I>(T const& a0, T const& a1, I const & i0)
// {
// // using v_t = eve::element_type_t<T>;
//   auto eve__tchebytchev  =  [](uint32_t n, auto x) { return eve::tchebytchev(n, x); };
//   for(unsigned int n=0; n < 6; ++n)
//   {
//     auto boost_tchebytchev =  [&](auto i, auto e) { return boost::math::chebyshev_t((unsigned int)i, e); };
//     TTS_ULP_EQUAL(eve__tchebytchev(n, a0), map(boost_tchebytchev, n, a0), 32);
//     TTS_ULP_EQUAL(eve__tchebytchev(n, a1), map(boost_tchebytchev, n, a1), 32);
//   }
//   auto boost_tchebytchev =  [&](auto i, auto e) { return boost::math::chebyshev_t(i, e); };
//   TTS_ULP_EQUAL(eve::tchebytchev(i0    , a0), map(boost_tchebytchev, i0, a0), 64);
//   TTS_ULP_EQUAL(eve::tchebytchev(i0    , a1), map(boost_tchebytchev, i0, a1), 64);
// };

// EVE_TEST( "Check behavior of kind_2(tchebytchev) on wide"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::between(-1.0, 1.0), eve::test::between(1.0, 10.0), eve::test::as_integer(eve::test::ramp(0)))
//         )
//   <typename T, typename I>(T const& a0, T const& a1, I const & i0)
// {
//   using eve::kind_2;
//   auto eve__tchebytchev  =  [](uint32_t n, auto x) { return eve::kind_2(eve::tchebytchev)(n, x); };
//   for(unsigned int n=0; n < 6; ++n)
//   {
//     auto boost_tchebytchev_u =  [&](auto i, auto e) { return boost::math::chebyshev_u((unsigned int)i, e); };
//     TTS_ULP_EQUAL(eve__tchebytchev(n, a0), map(boost_tchebytchev_u, n, a0), 1000);
//     TTS_ULP_EQUAL(eve__tchebytchev(n, a1), map(boost_tchebytchev_u, n, a1), 1000);
//   }
//   auto boost_tchebytchev_u =  [&](auto i, auto e) { return boost::math::chebyshev_u(i, e); };
//   TTS_ULP_EQUAL(kind_2(eve::tchebytchev)(i0    , a0), map(boost_tchebytchev_u, i0, a0), 64);
//   TTS_ULP_EQUAL(kind_2(eve::tchebytchev)(i0    , a1), map(boost_tchebytchev_u, i0, a1), 64);
// };

// EVE_TEST( "Check behavior of successor(tchebytchev)"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::between(-1.0, 1.0), eve::test::between(1.0, 10.0))
//         )
//   <typename T>(T const& a0, T const&)
// {
//   auto t3 = eve::tchebytchev(3, a0);
//   auto t4 = eve::tchebytchev(4, a0);
//   auto t5 = eve::tchebytchev(5, a0);
//   TTS_ULP_EQUAL(eve::successor(eve::tchebytchev)(a0, t4, t3), t5, 64);
//   using eve::kind_2;
//   auto u3 = kind_2(eve::tchebytchev)(3, a0);
//   auto u4 = kind_2(eve::tchebytchev)(4, a0);
//   auto u5 = kind_2(eve::tchebytchev)(5, a0);
//  TTS_ULP_EQUAL(eve::successor(eve::tchebytchev)(a0, u4, u3), u5, 100);
// };


//==================================================================================================
//== tchebytchev diff tests
//==================================================================================================
EVE_TEST( "Check behavior of diff tchebytchev on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::between(-1.0, 1.0))
        )
  <typename T>(T const& a0)
{

 for(int i=1; i < 10 ; ++i)
 {
   auto dt = eve::diff(eve::tchebytchev)(i, a0);
   auto u =  eve::kind_2(eve::tchebytchev)(i-1, a0);
   auto bdt1 = [&i](auto e){return boost::math::chebyshev_t_prime(i, e); };
   TTS_ULP_EQUAL(dt, u*i, 10);
   TTS_ULP_EQUAL(dt, eve::detail::map(bdt1, a0), 1000);
 }

 // there is no implementation in boost of chebyshev_u_prime so we will defer the test to the availability of
 // complex (vand) or ad (der) to test the derivative of second kind polynomials.
//  for(int i=1; i < 10 ; ++i)
//  {
//    auto dt = eve::diff(eve::tchebytchev)(i, a0);
//    auto bdt2 = [&i](auto e){return boost::math::chebyshev_u_prime(i, e); };
//    TTS_ULP_EQUAL(dt, eve::detail::map(bdt2, a0), 1000);
//  }
};
