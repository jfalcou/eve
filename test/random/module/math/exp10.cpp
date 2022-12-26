//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/math.hpp>
#include "producers.hpp"

#include <cmath>

TTS_CASE_TPL("Random check for eve::exp10", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::minlog10(eve::as<e_t>())+1;
  auto vmax = eve::maxlog10(eve::as<e_t>())-1;
  auto std_exp10 = [](auto e) -> e_t{ return ::exp10l(e); };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_exp10, eve::exp10 );
};
