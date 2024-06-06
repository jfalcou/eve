//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"

#include <cmath>

TTS_CASE_TPL("Random check for eve::rec", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;

  auto std_rec = [](auto e) { return 1/e; };
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  EVE_ULP_RANGE_CHECK ( T, eve::uniform_prng<e_t>(vmin,vmax), std_rec, eve::rec );
  EVE_ULP_RANGE_CHECK ( T, eve::uniform_prng<e_t>(vmin,vmax), std_rec, eve::rec[eve::pedantic2]);

};
