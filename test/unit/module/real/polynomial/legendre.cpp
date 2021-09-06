//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#define BOOST_MATH_OVERFLOW_ERROR_POLICY ignore_error
#include "test.hpp"
#include <boost/math/special_functions/legendre.hpp>
#include <eve/function/legendre.hpp>
#include <eve/function/diff/legendre.hpp>
#include <eve/function/is_odd.hpp>
#include <cmath>

// //==================================================================================================
// //== Types tests
// //==================================================================================================
// EVE_TEST_TYPES( "Check return types of legendre on wide"
//         , eve::test::simd::ieee_reals

//         )
// <typename T>(eve::as<T>)
// {
//   using v_t = eve::element_type_t<T>;
//   using wi_t = eve::as_integer_t<T>;
//   using i_t  = eve::as_integer_t<v_t>;
//   TTS_EXPR_IS( eve::legendre(i_t(), T())  , T);
//   TTS_EXPR_IS( eve::legendre(wi_t(), T())  , T);
//   TTS_EXPR_IS( eve::legendre(i_t(), v_t())  , v_t);
//   TTS_EXPR_IS( eve::legendre(wi_t(), v_t())  , T);

// };

// //==================================================================================================
// //== legendre tests
// //==================================================================================================
// EVE_TEST( "Check behavior of legendre p on wide"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::between(-1, 1), eve::test::as_integer(eve::test::ramp(0)))
//         )
//   <typename T, typename I>(T const& a0,I const & i0)
// {
//   using v_t = eve::element_type_t<T>;
//   auto eve__legendrev  =  [](auto n, auto x) { return eve::legendre(n, x); };
//   for(unsigned int n=0; n < 5; ++n)
//   {
//     auto boost_legendre =  [&](auto i, auto) { return boost::math::legendre_p(n, a0.get(i)); };
//     TTS_ULP_EQUAL(eve__legendrev(n, a0), T(boost_legendre), 100);
//   }
//   auto boost_legendrev =  [&](auto i, auto) { return boost::math::legendre_p(i0.get(i), a0.get(i)); };
//   TTS_ULP_EQUAL(eve__legendrev(i0    , a0), T(boost_legendrev), 100);
//   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
//   {
//     auto boost_legendre2 =  [&](auto i, auto) { return boost::math::legendre_p(i0.get(i), a0.get(j)); };
//     TTS_ULP_EQUAL(eve__legendrev(i0 , a0.get(j)), T(boost_legendre2), 100);
//   }
//   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
//   {
//     for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
//     {
//       TTS_ULP_EQUAL(eve__legendrev(i0.get(j) , a0.get(n)), v_t(boost::math::legendre_p(i0.get(j), a0.get(n))), 100);
//     }
//   }
// };

// //==================================================================================================
// //== legendre tests
// //==================================================================================================
// EVE_TEST( "Check behavior of legendre q on wide"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::between(-1.0, 1.0), eve::test::as_integer(eve::test::ramp(0)))
//         )
//   <typename T, typename I>(T const& a0,I const & i0)
// {
//   using v_t = eve::element_type_t<T>;
//   auto eve__legendrev  =  [](auto n, auto x) { return eve::q_kind(eve::legendre)(n, x); };
//   for(unsigned int n=0; n < 5; ++n)
//   {
//     auto boost_legendre =  [&](auto i, auto) { return boost::math::legendre_q(n, a0.get(i)); };
//     TTS_ULP_EQUAL(eve__legendrev(n, a0), T(boost_legendre), 100);
//   }

//   auto boost_legendrev =  [&](auto i, auto) { return boost::math::legendre_q(i0.get(i), a0.get(i)); };
//   TTS_ULP_EQUAL(eve__legendrev(i0    , a0), T(boost_legendrev), 100);
//   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
//   {
//     auto boost_legendre2 =  [&](auto i, auto) { return boost::math::legendre_q(i0.get(i), a0.get(j)); };
//     TTS_ULP_EQUAL(eve__legendrev(i0 , a0.get(j)), T(boost_legendre2), 100);
//   }

//   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
//   {
//     for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
//     {
//       TTS_ULP_EQUAL(eve__legendrev(i0.get(j) , a0.get(n)), v_t(boost::math::legendre_q(i0.get(j), a0.get(n))), 100);
//     }
//   }
// };

// EVE_TEST( "Check behavior of diff(legendre) on wide"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::between(-1, 1), eve::test::as_integer(eve::test::ramp(0)))
//         )
//   <typename T, typename I>(T const& a0,I const & i0)
// {
//   using v_t = eve::element_type_t<T>;
//   auto eve__legendrev  =  [](auto n, auto x) { return eve::diff(eve::legendre)(n, x); };
//   for(unsigned int n=0; n < 5; ++n)
//   {
//     auto boost_legendre =  [&](auto i, auto) { return boost::math::legendre_p_prime(n, a0.get(i)); };
//     TTS_ULP_EQUAL(eve__legendrev(n, a0), T(boost_legendre), 100);
//   }

//   auto boost_legendrev =  [&](auto i, auto) { return boost::math::legendre_p_prime(i0.get(i), a0.get(i)); };
//   TTS_ULP_EQUAL(eve__legendrev(i0    , a0), T(boost_legendrev), 100);

//   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
//   {
//     auto boost_legendre2 =  [i0, a0, j](auto i, auto) { return boost::math::legendre_p_prime(i0.get(i), a0.get(j)); };
//     TTS_ULP_EQUAL(eve__legendrev(i0 , a0.get(j)), T(boost_legendre2), 100);
//   }

//   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
//   {
//     for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
//     {
//       TTS_ULP_EQUAL(eve__legendrev(i0.get(j) , a0.get(n)), v_t(boost::math::legendre_p_prime(i0.get(j), a0.get(n))), 100);
//     }
//   }
// };

/////////////associated p legendre
EVE_TEST( "Check behavior of legendre q on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::between(-1.0, 1.0)
                             , eve::test::as_integer(eve::test::ramp(0))
                             , eve::test::as_integer(eve::test::reverse_ramp(0)))
        )
//     <typename T, typename I>(T const& a0,I const & i0,I const & j0)
     <typename T, typename I>(T const&   ,I const &   ,I const &   )
{
  using elt_t = eve::element_type_t<T>;
  auto eve__legendrev  =  [](auto m, auto n, auto x) { return eve::legendre(m, n, x); };
//  auto boost_legendrev =  [](auto m, auto n, auto x) { return boost::math::legendre_p(m, n, x); };
  auto legendrestd =[](auto m, auto n, auto x) { return (eve::is_odd(n) ? -1:1)*std::assoc_legendre(m, n, x); };
//  TTS_ULP_EQUAL(eve__legendrev(5, 3, elt_t(-1/3.0)), boost_legendrev(5, 3, -1/3.0), 100);
  for(unsigned int k=0; k < eve::cardinal_v < T > ; ++k)
  {
    for(unsigned int n=0; n < eve::cardinal_v < T > ; ++n)
    {
      for(unsigned int p=0; p < eve::cardinal_v < T > ; ++p)
      {
//        TTS_ULP_EQUAL(eve__legendrev(i0.get(n), j0.get(p), a0.get(k)), boost_legendrev(i0.get(n), j0.get(p), a0.get(k)), 100);
//        TTS_ULP_EQUAL(eve__legendrev(n        , p        , elt_t(-1/3.0)), boost_legendrev(n        , p        , elt_t(-1/3.0)), 100);
        TTS_ULP_EQUAL(eve__legendrev(n        , p        , elt_t(-1/3.0)), elt_t(legendrestd(n        , p        , double(elt_t(-1/3.0)))), 100);
        TTS_ULP_EQUAL(eve__legendrev(n        , p        , elt_t(-1/3.0)), elt_t(eve__legendrev(n        , p        , -1/3.0)), 100);
      }
    }
  }
//  TTS_ULP_EQUAL(eve__legendrev(i0, j0, a0), map(boost_legendrev(i0.get(1), j0.get(1), a0.get(1)), i0, j0, a0), 100);
//   for(unsigned int j=0; j < 5; ++j)
//   {
//     for(unsigned int n=0; n < 5; ++n)
//     {
//       std::cout << "l " << j << " --- m " << n << std::endl;
//       TTS_ULP_EQUAL(eve__legendrev(j , n, a0), map(boost_legendrev, j, n, a0), 100);
//     }
//   }
  //   for(unsigned int n=0; n < 5; ++n)
  //   {
  //     auto boost_legendre =  [&](auto i, auto) { return boost::math::legendre_q(n, a0.get(i)); };
  //     TTS_ULP_EQUAL(eve__legendrev(n, a0), T(boost_legendre), 100);
  //   }
//    auto boost_legendrev =  [&](auto i, auto) { return boost::math::legendre_p(i0.get(i), j0.get(i), a0.get(i)); };
//    TTS_ULP_EQUAL(eve__legendrev(i0, j0, a0), T(boost_legendrev), 100);
  //   using v_t = eve::element_type_t<T>;
  //   for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  //   {
  //     auto boost_legendre2 =  [&](auto i, auto) { return boost::math::legendre_q(i0.get(i), a0.get(j)); };
  //     TTS_ULP_EQUAL(eve__legendrev(i0 , a0.get(j)), T(boost_legendre2), 100);
  //   }
//   for(unsigned int i=0; i < 5u; ++i)
//   {
//     for(unsigned int j=0; j < 5u; ++j)
//     {
//       for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
//       {
//         std::cout << "a0 = " << a0.get(n) << " -- i = " << i << " -- j = " << j << std::endl;
//         TTS_ULP_EQUAL(eve__legendrev(i/*0.get(j), i0.get(j)*/, j, a0.get(n))
//                      , v_t(boost::math::legendre_p(i/*0.get(j), i0.get(j)*/, j, a0.get(n))), 100);
//       }
//     }
//   }


};
