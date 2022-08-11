//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

TTS_CASE_TPL("Random check for eve::average", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  auto std_average = [](auto e) { return std::midpoint(e, eve::one(eve::as(e))); };
  auto  my_average = [](auto e) { return eve::average (e, eve::one(eve::as(e))); };

  using e_t = eve::element_type_t<T>;
  eve::uniform_prng<e_t> p(eve::valmin(eve::as<e_t>()), eve::valmax(eve::as<e_t>()));

  if constexpr(eve::floating_value<e_t>)        EVE_ULP_RANGE_CHECK(T, p, std_average, my_average );
  else                                 EVE_ULP_RANGE_CHECK_WITH(T, p, std_average, my_average, 0.5);
};
