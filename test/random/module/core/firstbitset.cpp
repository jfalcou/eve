//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

TTS_CASE_TPL("Random check for eve::firstbitset", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  auto std_firstbitset = [](auto e) ->e_t { return e & (~e+1);};
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_firstbitset, eve::firstbitset );
};
