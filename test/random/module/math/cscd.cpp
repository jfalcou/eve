//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/math.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>

TTS_CASE_TPL("Random check for eve::cscd", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto std_cscd = [](auto e) -> e_t{ return 1.0l/(boost::math::sin_pi(((long double)e)/180.0l)); };
  {
    auto vmin = e_t(-45.);
    auto vmax = e_t(45.);
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_cscd, eve::cscd );
  }
  {
    auto vmin = e_t(-90.);
    auto vmax = e_t(90.);
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_cscd, eve::cscd );
  }
  {
    auto vmin = e_t(-180.);
    auto vmax = e_t(180.);
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_cscd, eve::cscd );
  }
  {
    auto vmin = e_t(-5000.);
    auto vmax = e_t(5000.);
    EVE_ULP_RANGE_CHECK_WITH( T, eve::uniform_prng<e_t>(vmin, vmax),  std_cscd, eve::cscd,  16);
  }

};
