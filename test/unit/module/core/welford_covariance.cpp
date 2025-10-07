//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of welford_covariance", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using welford_covariance_result_t = eve::detail::welford_covariance_result<T>;

  // multi
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::welford_covariance(T(), T(), T(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(T(), v_t(), T(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(v_t(), T(), T(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(T(), T(), v_t(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(v_t(), v_t(), T(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(v_t(), T(), v_t(), T()), welford_covariance_result_t);
    TTS_EXPR_IS(eve::welford_covariance(v_t(), v_t(), v_t()), eve::detail::welford_covariance_result<v_t>);
  }
};

//==================================================================================================
//== welford_covariance tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of welford_covariance(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::welford_covariance;
  using eve::sqr;
  // std::cout << "a0 " << a0 << std::endl;
  // std::cout << "a1 " << a1 << std::endl;
  // std::cout << "a2 " << a2 << std::endl;
  // std::cout << "a3 " << a3 << std::endl;
  // std::cout << "c  " << welford_covariance(a0, a1, a2, a3, sqr(a0), sqr(a1), sqr(a2), sqr(a3)).covariance<< std::endl;
  // std::cout << "c  " << eve::covariance(a0, a1, a2, a3, sqr(a0), sqr(a1), sqr(a2), sqr(a3))<< std::endl;
  TTS_ULP_EQUAL(welford_covariance(a0, a1, a2, a3, sqr(a0), sqr(a1), sqr(a2), sqr(a3)).covariance,
                eve::covariance(a0, a1, a2, a3, sqr(a0), sqr(a1), sqr(a2), sqr(a3)), 1.5);
};

TTS_CASE_WITH("Check behavior of welford_covariance  on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
  <typename T>(T const& a0, T const& a1,  T const& a2,  T const& )
{
  using eve::welford_covariance;
  using eve::welford_variance;
  using eve::sqr;
  // std::cout << "a0 " << a0 << std::endl;
  // std::cout << "a1 " << a1 << std::endl;
  // std::cout << "a2 " << a2 << std::endl;
  // std::cout << "a3 " << a3 << std::endl;

  auto a = welford_covariance(a0, a1, sqr(a0), sqr(a1));
  auto b = welford_covariance(a2, sqr(a2));
  // std::cout << "a " << a.averagex << std::endl;
  // std::cout << "a " << a.averagey << std::endl;
  // std::cout << "a " << a.mxy      << std::endl;
  // std::cout << "a " << a.covariance<< std::endl;
  // std::cout << "a " << a.count     << std::endl;
  // std::cout << "b " << b.averagex << std::endl;
  // std::cout << "b " << b.averagey << std::endl;
  // std::cout << "b " << b.mxy      << std::endl;
  // std::cout << "b " << b.covariance<< std::endl;
  // std::cout << "b " << b.count     << std::endl;
//  auto scal = welford_covariance(a);
//  scal.print("scal");

  // std::cout << welford_covariance(a, b)<< std::endl;
//   welford_covariance(a, b).print("wcovariance(a, b)");
//   welford_covariance(a0, a1, a2, sqr(a0), sqr(a1), sqr(a2)).print("wcovariance(a0, ...)");
  // std::cout <<  tts::typename_<decltype(welford_covariance(a, b).covariance)> << std::endl;
  // std::cout <<  tts::typename_<decltype(eve::welford_covariance(a0, a1, a2, sqr(a0), sqr(a1), sqr(a2)).covariance)> << std::endl;
  TTS_ULP_EQUAL(welford_covariance(a, b).covariance, eve::welford_covariance(a0, a1, a2, sqr(a0), sqr(a1), sqr(a2)).covariance, 1.5);

  TTS_ULP_EQUAL(welford_covariance(1.0f, 2.0f, -3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 48.0f, 9.0f, 10.0f).covariance,
                   eve::covariance(1.0f, 2.0f, -3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 48.0f, 9.0f, 10.0f), 1.0f);

  TTS_ULP_EQUAL(welford_covariance(eve::wide(1.0f), eve::wide( 2.0f), eve::wide( -3.0f), eve::wide( 4.0f),
                                   eve::wide( 5.0f), eve::wide( 6.0f), eve::wide( 7.0f), eve::wide( 48.0f), eve::wide( 9.0f), eve::wide( 10.0f)).covariance,
                eve::covariance(eve::wide(1.0f), eve::wide( 2.0f), eve::wide( -3.0f), eve::wide( 4.0f),
                                eve::wide( 5.0f), eve::wide( 6.0f), eve::wide( 7.0f), eve::wide( 48.0f), eve::wide( 9.0f), eve::wide( 10.0f)), 1.0f);
  TTS_ULP_EQUAL(welford_covariance(1.0f, 2.0f, -3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 48.0f, -3.0f, 2.9f).covariance,
                eve::covariance(1.0f, 2.0f, -3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 48.0f, -3.0f, 2.9f), 1.0f);
 //   auto aa = kumi::make_tuple(1.0f, 2.0f, -3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 48.0f, -3.0f, 2.9f);
//    auto bb = kumi::make_tuple(6.0f, 7.0f, -0.0f, 4.0f, 5.0f, 3.0f,-7.0f, 48.0f, -3.0f, 2.9f);
//    TTS_ULP_EQUAL(welford_covariance(aa, bb).covariance,  eve::covariance(aa, bb), 1.0);
};
