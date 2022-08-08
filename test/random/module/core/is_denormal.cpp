//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

TTS_CASE_TPL("Random check for eve::is_denormal", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  if constexpr(eve::floating_value<e_t>)
  {
    auto std_is_denormal = [](auto e) -> eve::logical<e_t>{ return std::fpclassify(e) == FP_SUBNORMAL; };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_is_denormal, eve::is_denormal );
  }
  else
  {
    auto std_is_denormal = [](auto e) { return eve::false_(eve::as(e)); };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_is_denormal, eve::is_denormal );
  }
};
