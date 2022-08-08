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
#include <bit>

TTS_CASE_TPL("Random check for eve::minus", eve::test::simd::signed_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  auto std_saturated_minus = [vmin, vmax](auto e) -> e_t { return (e == vmin) ? vmax :-e; };
  auto std_minus = [](auto e) -> e_t { return -e; };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin+1, vmax), std_minus, eve::minus );
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin,   vmax), std_saturated_minus, eve::saturated(eve::minus) );
 };
