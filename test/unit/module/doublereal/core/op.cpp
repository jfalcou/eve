//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_TPL( "Check doublereal::operator+= ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using doublereal_t   = eve::doublereal<T>;
  // using w_t    = eve::wide<T>;
  //  using wdoublereal_t  = eve::wide<doublereal_t>;
  if constexpr(sizeof(T) == 4)
  {
    double pi = eve::pi(eve::as<double>());
    auto doublerealpi = doublereal_t(pi);
    TTS_ULP_EQUAL(pi, eve::to_double(doublerealpi), 4);
    doublerealpi = doublerealpi +  doublerealpi;
    TTS_ULP_EQUAL(2*pi, eve::to_double(doublerealpi), 4);
    doublerealpi =  doublerealpi + 1.2345f;
    TTS_ULP_EQUAL(2*pi+1.2345f, eve::to_double(doublerealpi), 4);
  }
};

TTS_CASE_TPL( "Check doublereal::operator-= ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using doublereal_t   = eve::doublereal<T>;
  // using w_t    = eve::wide<T>;
  //  using wdoublereal_t  = eve::wide<doublereal_t>;
  if constexpr(sizeof(T) == 4)
  {
    double pi = eve::pi(eve::as<T>());
    double e  = eve::euler(eve::as<T>());
    auto doublerealpi = doublereal_t(pi);
    TTS_ULP_EQUAL(pi, eve::to_double(doublerealpi), 4);
    doublerealpi =  doublerealpi -e;
    TTS_ULP_EQUAL(pi-e, eve::to_double(doublerealpi), 4);
    doublerealpi =  doublerealpi -1.2345f;
    TTS_ULP_EQUAL((pi-e)-1.2345f, eve::to_double(doublerealpi), 4);
  }
};

TTS_CASE_TPL( "Check doublereal::operator*= ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using doublereal_t   = eve::doublereal<T>;
  // using w_t    = eve::wide<T>;
  //  using wdoublereal_t  = eve::wide<doublereal_t>;
  if constexpr(sizeof(T) == 4)
  {
    double pi = eve::pi(eve::as<double>());
    double e  = eve::euler(eve::as<double>());
    auto doublerealpi = doublereal_t(pi);
    std::cout << doublerealpi << std::endl;
    TTS_ULP_EQUAL(pi, eve::to_double(doublerealpi), 4);
    doublerealpi =  doublerealpi * e;
    TTS_ULP_EQUAL(pi*e, eve::to_double(doublerealpi), 6);
    doublerealpi =  doublerealpi * 1.2345f;
    TTS_ULP_EQUAL((pi*e)*1.2345f, eve::to_double(doublerealpi), 8);
  }
};

TTS_CASE_TPL( "Check doublereal::operator/= ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using doublereal_t   = eve::doublereal<T>;
  // using w_t    = eve::wide<T>;
  //  using wdoublereal_t  = eve::wide<doublereal_t>;
  if constexpr(sizeof(T) == 4)
  {
    double pi = eve::pi(eve::as<double>());
    double e  = eve::euler(eve::as<double>());
    auto doublerealpi = doublereal_t(pi);
    TTS_ULP_EQUAL(pi, eve::to_double(doublerealpi), 4);
    doublerealpi = doublerealpi / doublereal_t(e);
    TTS_ULP_EQUAL(pi/e, eve::to_double(doublerealpi), 4);
    doublerealpi = doublerealpi /  1.2345f;
    TTS_ULP_EQUAL((pi/e)/1.2345f, eve::to_double(doublerealpi), 4);
  }
};
