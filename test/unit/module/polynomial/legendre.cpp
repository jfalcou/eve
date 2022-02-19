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
#include <boost/math/special_functions/spherical_harmonic.hpp>
#include <eve/module/polynomial.hpp>
#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of legendre on wide"
              , eve::test::simd::ieee_reals

              )
  <typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using wi_t = eve::as_integer_t<T>;
  using i_t  = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::legendre(i_t(), T())  , T);
  TTS_EXPR_IS( eve::legendre(wi_t(), T())  , T);
  TTS_EXPR_IS( eve::legendre(i_t(), v_t())  , v_t);
  TTS_EXPR_IS( eve::legendre(wi_t(), v_t())  , T);

};

//==================================================================================================
//== legendre tests
//==================================================================================================
EVE_TEST( "Check behavior of legendre p on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::between(-1, 1), eve::test::as_integer(eve::test::ramp(0)))
        )
  <typename T, typename I>(T const& a0,I const & i0)
{
  using v_t = eve::element_type_t<T>;
  auto eve__legendrev  =  [](auto n, auto x) { return eve::legendre(n, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_legendre =  [&](auto i, auto) { return boost::math::legendre_p(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve__legendrev(n, a0), T(boost_legendre), 100);
  }
  auto boost_legendrev =  [&](auto i, auto) { return boost::math::legendre_p(i0.get(i), a0.get(i)); };
  TTS_ULP_EQUAL(eve__legendrev(i0    , a0), T(boost_legendrev), 100);
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_legendre2 =  [&](auto i, auto) { return boost::math::legendre_p(i0.get(i), a0.get(j)); };
    TTS_RELATIVE_EQUAL(eve__legendrev(i0 , a0.get(j)), T(boost_legendre2), 0.01);
  }
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_RELATIVE_EQUAL(eve__legendrev(i0.get(j) , a0.get(n)), v_t(boost::math::legendre_p(i0.get(j), a0.get(n))), 0.01);
    }
  }
};

//==================================================================================================
//== legendre tests
//==================================================================================================
EVE_TEST( "Check behavior of legendre q on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::between(-1.0, 1.0), eve::test::as_integer(eve::test::ramp(0)))
        )
  <typename T, typename I>(T const& a0,I const & i0)
{
  using v_t = eve::element_type_t<T>;
  auto eve__legendrev  =  [](auto n, auto x) { return eve::q_kind(eve::legendre)(n, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_legendre =  [&](auto i, auto) { return boost::math::legendre_q(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve__legendrev(n, a0), T(boost_legendre), 100);
  }

  auto boost_legendrev =  [&](auto i, auto) { return boost::math::legendre_q(i0.get(i), a0.get(i)); };
  TTS_ULP_EQUAL(eve__legendrev(i0    , a0), T(boost_legendrev), 100);
  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_legendre2 =  [&](auto i, auto) { return boost::math::legendre_q(i0.get(i), a0.get(j)); };
    TTS_RELATIVE_EQUAL(eve__legendrev(i0 , a0.get(j)), T(boost_legendre2),  0.01);
  }

  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_RELATIVE_EQUAL(eve__legendrev(i0.get(j) , a0.get(n)), v_t(boost::math::legendre_q(i0.get(j), a0.get(n))), 0.01);
    }
  }
};

EVE_TEST( "Check behavior of diff(legendre) on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::between(-1, 1), eve::test::as_integer(eve::test::ramp(0)))
        )
  <typename T, typename I>(T const& a0,I const & i0)
{
  using v_t = eve::element_type_t<T>;
  auto eve__legendrev  =  [](auto n, auto x) { return eve::diff(eve::legendre)(n, x); };
  for(unsigned int n=0; n < 5; ++n)
  {
    auto boost_legendre =  [&](auto i, auto) { return boost::math::legendre_p_prime(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve__legendrev(n, a0), T(boost_legendre), 100);
  }

  auto boost_legendrev =  [&](auto i, auto) { return boost::math::legendre_p_prime(i0.get(i), a0.get(i)); };
  TTS_ULP_EQUAL(eve__legendrev(i0    , a0), T(boost_legendrev), 100);

  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    auto boost_legendre2 =  [i0, a0, j](auto i, auto) { return boost::math::legendre_p_prime(i0.get(i), a0.get(j)); };
    TTS_RELATIVE_EQUAL(eve__legendrev(i0 , a0.get(j)), T(boost_legendre2), 0.01);
  }

  for(unsigned int j=0; j < eve::cardinal_v<T>; ++j)
  {
    for(unsigned int n=0; n < eve::cardinal_v<T>; ++n)
    {
      TTS_RELATIVE_EQUAL(eve__legendrev(i0.get(j) , a0.get(n)), v_t(boost::math::legendre_p_prime(i0.get(j), a0.get(n))), 0.01);
    }
  }
};

/////////////associated p legendre
EVE_TEST( "Check behavior of associated legendre p on wide"
        , eve::test::simd::ieee_doubles
        , eve::test::generate(eve::test::between(-1.0, 1.0)
                             , eve::test::as_integer(eve::test::ramp(0))
                             , eve::test::as_integer(eve::test::reverse_ramp(0)))
        )
  <typename T, typename I>(T a0, I i0, I j0)
{
  auto cse__legendrev  =  [](auto m, auto n, auto x) { return eve::condon_shortey(eve::legendre)(m, n, x); };
  auto boost_legendrev =  [](auto m, auto n, auto x) { return boost::math::legendre_p(m, n, x); };

#if defined(__cpp_lib_math_special_functions)
  auto eve__legendrev  =  [](auto m, auto n, auto x) { return eve::legendre(m, n, x); };
  auto std_assoc = [](auto m, auto n, auto x) { return std::assoc_legendre(m, n, x); };
#endif

  for(unsigned int k=0; k < eve::cardinal_v < T > ; ++k)
  {
    for(unsigned int n=0; n < eve::cardinal_v < I > ; ++n)
    {
      for(unsigned int p=0; p < eve::cardinal_v < I > ; ++p)
      {
#if defined(__cpp_lib_math_special_functions)
        TTS_ULP_EQUAL(eve__legendrev(n, p, a0.get(k)), std_assoc(n, p, a0.get(k)), 100);
#endif

        TTS_RELATIVE_EQUAL(cse__legendrev(n, p, a0.get(k)), boost_legendrev(n, p, a0.get(k)), 0.01);
      }
    }
  }

#if defined(__cpp_lib_math_special_functions)
  TTS_ULP_EQUAL(eve__legendrev(j0, i0, a0), map(std_assoc, j0, i0, a0), 100);
#endif

  TTS_ULP_EQUAL(cse__legendrev(i0, j0, a0), map(boost_legendrev, i0, j0, a0), 100);
};

/////////////spherical legendre
EVE_TEST( "Check behavior of spherical legendre on wide"
        , eve::test::simd::ieee_doubles
        , eve::test::generate(eve::test::between(0, 3.14159)
                             , eve::test::as_integer(eve::test::ramp(0))
                             , eve::test::as_integer(eve::test::reverse_ramp(0)))
        )
  <typename T, typename I>(T a0, I i0, I j0)
{
  auto eve__slegendre  =  [](auto m, auto n, auto x) { return eve::sph(eve::legendre)(m, n, x); };

#if defined(__cpp_lib_math_special_functions)
  auto std_slegendre = [](auto m, auto n, auto x) { return std::sph_legendre(m, n, x); };
#else
  auto boost_slegendre =  [](auto m, auto n, auto x) { return boost::math::spherical_harmonic_r(m, n, x, 0);};
#endif

  for(unsigned int k=0; k < eve::cardinal_v < T > ; ++k)
  {
    for(unsigned int n=0; n < eve::cardinal_v < I > ; ++n)
    {
      for(unsigned int p=0; p < n ; ++p)
      {
#if defined(__cpp_lib_math_special_functions)
        TTS_RELATIVE_EQUAL(eve__slegendre(n, p, a0.get(k)), std_slegendre(n, p, a0.get(k)), 0.001);
#else
        TTS_RELATIVE_EQUAL(eve__slegendre(n, p, a0.get(k)), boost_slegendre(n, p, a0.get(k)), 0.001);
#endif
      }
    }
  }

  j0 = eve::min(i0, j0);
#if defined(__cpp_lib_math_special_functions)
  TTS_ULP_EQUAL(eve__slegendre(i0, j0, a0), map(std_slegendre, i0, j0, a0), 100);
#else
  TTS_RELATIVE_EQUAL(eve__slegendre(i0, j0, a0), map(boost_slegendre, i0, j0, a0), 0.001);
#endif
};
