//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

TTS_CASE_TPL("Random check for eve::frac", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  if constexpr(eve::floating_value<e_t>)
  {
    auto std_frac = [](auto e) -> e_t { return e-trunc(e); };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_frac, eve::frac );
  }
  else
  {
    auto std_frac = [](auto e) -> e_t { return eve::zero(eve::as(e)); };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_frac, eve::frac );
  }

};
