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
#include <cmath>

TTS_CASE_TPL("Random check for eve::tan", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  auto std_tan = [](auto e) { return std::tan(e); };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_tan, eve::tan );
};
