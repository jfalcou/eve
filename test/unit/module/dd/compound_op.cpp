//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/dd.hpp>

TTS_CASE_TPL( "Check dd::operator+= ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using dd_t   = eve::dd<T>;
  // using w_t    = eve::wide<T>;
  //  using wdd_t  = eve::wide<dd_t>;
  if constexpr(sizeof(T) == 4)
  {
    double pi = eve::pi(eve::as<double>());
    auto ddpi = dd_t(pi);
    std::cout << ddpi << std::endl;
    TTS_ULP_EQUAL(pi, eve::to_double(ddpi), 4);
    ddpi +=  ddpi;
    TTS_ULP_EQUAL(2*pi, eve::to_double(ddpi), 4);
    ddpi +=  1.2345f;
    TTS_ULP_EQUAL(2*pi+1.2345f, eve::to_double(ddpi), 4);
  }
};

TTS_CASE_TPL( "Check dd::operator-= ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using dd_t   = eve::dd<T>;
  // using w_t    = eve::wide<T>;
  //  using wdd_t  = eve::wide<dd_t>;
  if constexpr(sizeof(T) == 4)
  {
    double pi = eve::pi(eve::as<T>());
    double e  = eve::euler(eve::as<T>());
    auto ddpi = dd_t(pi);
    std::cout << ddpi << std::endl;
    TTS_ULP_EQUAL(pi, eve::to_double(ddpi), 4);
    ddpi -=  e;
    TTS_ULP_EQUAL(pi-e, eve::to_double(ddpi), 4);
    ddpi -=  1.2345f;
    TTS_ULP_EQUAL((pi-e)-1.2345f, eve::to_double(ddpi), 4);
  }
};

TTS_CASE_TPL( "Check dd::operator*= ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using dd_t   = eve::dd<T>;
  // using w_t    = eve::wide<T>;
  //  using wdd_t  = eve::wide<dd_t>;
  if constexpr(sizeof(T) == 4)
  {
    double pi = eve::pi(eve::as<double>());
    double e  = eve::euler(eve::as<double>());
    auto ddpi = dd_t(pi);
    std::cout << ddpi << std::endl;
    TTS_ULP_EQUAL(pi, eve::to_double(ddpi), 4);
    ddpi *=  e;
    TTS_ULP_EQUAL(pi*e, eve::to_double(ddpi), 6);
    ddpi *=  1.2345f;
    TTS_ULP_EQUAL((pi*e)*1.2345f, eve::to_double(ddpi), 8);
  }
};

TTS_CASE_TPL( "Check dd::operator/= ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using dd_t   = eve::dd<T>;
  // using w_t    = eve::wide<T>;
  //  using wdd_t  = eve::wide<dd_t>;
  if constexpr(sizeof(T) == 4)
  {
    double pi = eve::pi(eve::as<double>());
    double e  = eve::euler(eve::as<double>());
    auto ddpi = dd_t(pi);
    std::cout << ddpi << std::endl;
    TTS_ULP_EQUAL(pi, eve::to_double(ddpi), 4);
    ddpi /=  dd_t(e);
    TTS_ULP_EQUAL(pi/e, eve::to_double(ddpi), 4);
    ddpi /=  1.2345f;
    TTS_ULP_EQUAL((pi/e)/1.2345f, eve::to_double(ddpi), 4);
  }
};
