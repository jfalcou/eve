//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/math.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

TTS_CASE_TPL("Random check for eve::acosd", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::mone(eve::as<e_t>());
  auto vmax = eve::one(eve::as<e_t>());
  auto std_acosd = [](auto e) { return eve::radindeg(std::acos(e)); };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_acosd, eve::acosd );
  auto vmaxr = e_t(0.9);
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmaxr),  std_acosd, eve::raw(eve::acosd) );


};
